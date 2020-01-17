#include <functional>
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <ignition/math/Pose3.hh>
#include <ignition/math/Vector3.hh>
#include <thread>
#include <thread>
#include "ros/ros.h"
#include "ros/callback_queue.h"
#include "ros/subscribe_options.h"
#include "std_msgs/Float32.h"

namespace gazebo
{
  class PietonPlugin : public ModelPlugin
  {
    public: virtual void Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf)
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
       "/" + this->model->GetName() + "/pieton_velocity",
       1,
       boost::bind(&PietonPlugin::OnRosMsg, this, _1),
       ros::VoidPtr(), &this->rosQueue);
      this->rosSub = this->rosNode->subscribe(so);

      // Spin up the queue helper thread.
      this->rosQueueThread = std::thread(std::bind(&PietonPlugin::QueueThread, this));

    }

    public: void SetVelocity(const double &_velocity)
    // Sets position of the barrier
    {
	std::cerr << "Set Velocity" << std::endl;
      link->SetLinearVel({_velocity, 0, 0});   // Set velocity of the link
    }

    /// \brief Handle an incoming message from ROS
    /// \param[in] _msg A float value that is used to set the velocity
    public: void OnRosMsg(const std_msgs::Float32ConstPtr &_msg)
    {
	std::cerr << _msg->data << std::endl;
      this->SetVelocity(_msg->data);
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
  GZ_REGISTER_MODEL_PLUGIN(PietonPlugin)
}
