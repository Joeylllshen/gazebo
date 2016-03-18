/*
 * Copyright (C) 2012-2016 Open Source Robotics Foundation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
*/
#ifndef _GAZEBO_PHYSICS_SIMBODY_SIMBODYJOINTPRIVATE_HH_
#define _GAZEBO_PHYSICS_SIMBODY_SIMBODYJOINTPRIVATE_HH_

namespace gazebo
{
  namespace physics
  {
    /// \internal
    /// \brief Private data for SimbodyJoint
    class SimbodyJointPrivate
    {
      /// \brief Force Simbody to break a loop by using a weld constraint.
      /// This flag is needed by SimbodyPhysics::MultibodyGraphMaker, so kept
      /// public.
      public: bool mustBreakLoopHere;

      /// \brief Normally A=F, B=M. But if reversed, then B=F, A=M.
      /// parent body frame to mobilizer frame
      public: SimTK::Transform xPA;

      /// \brief child body frame to mobilizer frame
      public: SimTK::Transform xCB;

      /// \brief default mobilizer pose
      public: SimTK::Transform defxAB;

      /// \brief: Spring force element for enforcing joint stiffness.
      /// The element is assigned when constructing Simbody model in
      /// SimbodyPhysics::AddDynamicModelToSimbodySystem.
      /// \TODO: Also, consider moving this into individual joint type subclass
      /// so we can specify custom springs for special joints like ball joints.
      public: SimTK::Force::MobilityLinearSpring spring[MAX_JOINT_AXIS];

      /// \brief: for enforcing joint damping forces.
      /// Set when we build the Simbody model.
      /// \TODO: Also, consider moving this into individual joint type subclass
      /// so we can specify custom dampers for special joints like ball joints.
      public: SimTK::Force::MobilityLinearDamper damper[MAX_JOINT_AXIS];

      /// \brief: for enforcing joint stops
      /// Set when we build the Simbody model.
      /// \TODO: Also, consider moving this into individual joint type subclass
      /// so we can specify custom dampers for special joints like ball joints.
      /// Assuming this is not used for BallJoints it's ok here for now.
      public: SimTK::Force::MobilityLinearStop limitForce[MAX_JOINT_AXIS];

      /// \brief Use isValid() if we used a mobilizer
      /// Set when we build the Simbody model.
      /// How this joint was modeled in the Simbody System. We used either a
      /// mobilizer or a constraint, but not both. The type of either one is
      /// the same as the joint type above.
      public: SimTK::MobilizedBody mobod;

      /// \brief: if mobilizer, did it reverse parent&child?
      /// Set when we build the Simbody model.
      public: bool isReversed;

      /// \brief: isValid() if we used a constraint to model this joint.
      /// Set when we build the Simbody model.
      /// How this joint was modeled in the Simbody System. We used either a
      /// mobilizer or a constraint, but not both. The type of either one is the
      /// same as the joint type above.
      public: SimTK::Constraint constraint;

      // Keeps track if simbody physics has been initialized
      public: bool physicsInitialized;

      /// \brief Simbody Multibody System
      public: SimTK::MultibodySystem *world;

      /// \brief keep a pointer to the simbody physics engine for convenience
      public: SimbodyPhysicsPtr simbodyPhysics;

      /// \brief Save force applied by user
      /// This plus the joint feedback (joint contstraint forces) is the
      /// equivalent of simulated force torque sensor reading
      /// Allocate a 2 vector in case hinge2 joint is used.
      /// This is used by Bullet to store external force applied by the user.
      /// \TODO: Also, consider moving this into individual joint type subclass
      /// so we can specify custom dampers for special joints like ball joints.
      /// Assuming this is not used for BallJoints it's ok here for now.
      public: double forceApplied[MAX_JOINT_AXIS];

      /// \brief Save time at which force is applied by user
      /// This will let us know if it's time to clean up forceApplied.
      public: common::Time forceAppliedTime;
    };
  }
}
#endif