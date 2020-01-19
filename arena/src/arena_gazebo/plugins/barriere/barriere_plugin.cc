#include <functional>
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <ignition/math/Pose3.hh>
#include <ignition/math/Vector3.hh>
#include <ignition/math/Quaternion.hh>
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

      // Store the pointer to the model
      this->model = _parent;
      this->link = this->model->GetLinks()[0];

      // Initialize ros, if it has not already been initialized.
      if (!ros::isInitialized())
      {
  	int argc = 0;
  	char **argv = NULL;
  	ros::init(argc, argv, "gazebo",
      	ros::init_options::NoSigintHandler);
      }

      // Create our ROS node. This acts in a similar manner to
      // the Gazebo node
      this->rosNode.reset(new ros::NodeHandle("gazebo"));

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

    public: void SetPosition(const double &_position)
    // Sets position of the barrier
    {
      ignition::math::Pose3d pose;

      if (_position == 0)
      {
        ignition::math::Vector3<double> position_closed(0.14, 1.0, 0.1); // Closed barrier shift
	pose.Pos() = position_closed;
	this->model->SetLinkWorldPose(pose, this->link); // Set the position of the barrier
      }
      else if (_position == 1)
      {
     	ignition::math::Quaternion<double> rot(0.707/2, 0, 0, 0.707/2); // Opened barrier rotation
        ignition::math::Vector3<double> position_opened(0.30, 0.87, 0.1); // Opened barrier shift
        pose.Rot() = rot;
	pose.Pos() = position_opened;
	this->model->SetLinkWorldPose(pose, this->link); // Set the position of the barrier
      }	
    }

    /// \brief Handle an incoming message from ROS
    /// \param[in] _msg A float value that is used to set the position
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
