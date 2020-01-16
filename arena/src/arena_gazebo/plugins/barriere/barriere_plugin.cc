#include <functional>
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <gazebo/transport/transport.hh>
#include <gazebo/msgs/msgs.hh>
#include <ignition/math/Pose3.hh>
#include <ignition/math/Vector3.hh>
#include <thread>
#include "ros/ros.h"
#include "ros/callback_queue.h"
#include "ros/subscribe_options.h"
#include "std_msgs/Float32.h"

namespace gazebo
{
  class BarrierPlugin : public ModelPlugin
  {
    public: void Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf)
    {

      double position = 0; // Position of the barrier 0 is closed 1 is opened

      // Store the pointer to the model
      this->model = _parent;
      this->link = this->model->GetLinks()[0];
      
      
      // Check that element position exists and recuperate value
      if (_sdf->HasElement("position"))
	{
	  position = _sdf->Get<double>("position");
	}

      // Create the node
      this->node = transport::NodePtr(new transport::Node());
      this->node->Init(this->model->GetName());

      // Create a topic name
      std::string topicName = "~/" + this->model->GetName() + "/barriere_position";

      // Subscribe to the topic, and register a callback
      this->sub = this->node->Subscribe(topicName, &BarrierPlugin::OnMsg, this);

      // Initialize ros, if it has not already bee initialized.
      if (!ros::isInitialized())
      {
  	int argc = 0;
  	char **argv = NULL;
  	ros::init(argc, argv, "gazebo_client",
      	ros::init_options::NoSigintHandler);
      }

      // Create our ROS node. This acts in a similar manner to
      // the Gazebo node
      this->rosNode.reset(new ros::NodeHandle("gazebo_client"));

      // Create a named topic, and subscribe to it.
      ros::SubscribeOptions so = ros::SubscribeOptions::create<std_msgs::Float32>(
       "/" + this->model->GetName() + "/barriere_position",
       1,
       boost::bind(&BarrierPlugin::OnRosMsg, this, _1),
       ros::VoidPtr(), &this->rosQueue);
      this->rosSub = this->rosNode->subscribe(so);

      // Spin up the queue helper thread.
      this->rosQueueThread = std::thread(std::bind(&BarrierPlugin::QueueThread, this));

    }

    public: void SetPosition(const int &_position)
    // Sets position of the barrier
    {
      ignition::math::Vector3<double> position_closed(-1, -0.14, 2);
      ignition::math::Vector3<double> position_opened(0, 0, 2);
      ignition::math::Pose3d pose;

      if (_position == 0)
      {
	pose.Pos() = position_closed;
	this->model->SetLinkWorldPose(pose, this->link);
      }
      else if (_position == 1)
      {
	pose.Pos() = position_opened;
	this->model->SetLinkWorldPose(pose, this->link);
      }	
    }

    /// \brief Handle incoming message
    /// \param[in] _msg Int for barrier position
    private: void OnMsg(ConstVector3dPtr &_msg)
    {
      this->SetPosition(_msg->x());
    }

    /// \brief Handle an incoming message from ROS
    /// \param[in] _msg A float value that is used to set the velocity
    /// of the Velodyne.
    public: void OnRosMsg(const std_msgs::Float32ConstPtr &_msg)
    {
      this->SetPosition(_msg->data);
    }

    /// \brief ROS helper function that processes messages
    private: void QueueThread()
    {
      static const double timeout = 0.01;
      while (this->rosNode->ok())
      {
      this->rosQueue.callAvailable(ros::WallDuration(timeout));
      }
    }

    /// \brief A node use for ROS transport
    private: std::unique_ptr<ros::NodeHandle> rosNode;

    /// \brief A ROS subscriber
    private: ros::Subscriber rosSub;

    /// \brief A ROS callbackqueue that helps process messages
    private: ros::CallbackQueue rosQueue;

    /// \brief A thread the keeps running the rosQueue
    private: std::thread rosQueueThread;

    /// A node used for transport
    private: transport::NodePtr node;

    // A subscriber to a named topic.
    private: transport::SubscriberPtr sub;

    // Pointer to the model
    private: physics::ModelPtr model;

    // Pointer to links
    private: physics::LinkPtr link;

    // Pointer to the update event connection
    private: event::ConnectionPtr updateConnection;
  };

  // Register this plugin with the simulator
  GZ_REGISTER_MODEL_PLUGIN(BarrierPlugin)
}
