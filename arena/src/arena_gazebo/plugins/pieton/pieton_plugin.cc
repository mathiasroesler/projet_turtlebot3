#include <functional>
#include <gazebo/gazebo.hh>
#include <gazebo/physics/physics.hh>
#include <gazebo/common/common.hh>
#include <ignition/math/Pose3.hh>
#include <ignition/math/Vector3.hh>
#include <ignition/math/Quaternion.hh>
#include <chrono>
#include <thread>

namespace gazebo
{
  class PietonPlugin : public ModelPlugin
  {
    public: virtual void Load(physics::ModelPtr _parent, sdf::ElementPtr _sdf)
    {
      // Store the pointer to the model
      this->model = _parent;

      // Listen to the update event. This event is broadcast every
      // simulation iteration.
      this->updateConnection = event::Events::ConnectWorldUpdateBegin(std::bind(&PietonPlugin::OnUpdate, this));

    }

    // Called by the world update start event
    public: void OnUpdate()
    {
      this->link = model->GetLinks()[0]; // Get link of model
      link->SetLinearVel({0.3, 0, 0});   // Set velocity of the link

    }

    // Pointer to the model
    private: physics::ModelPtr model;

    // Pointer to the links
    private: physics::LinkPtr link;

    // Pointer to the update event connection
    private: event::ConnectionPtr updateConnection;
  };

  // Register this plugin with the simulator
  GZ_REGISTER_MODEL_PLUGIN(PietonPlugin)
}
