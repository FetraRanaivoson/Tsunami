#pragma once
#include "Core.h"
using namespace tsunami;

	/**
	The simplest object that can be simulated in physics system
	*/
	class Particle {
	public:
		/*Linear position of the particle in world space*/
		Vector3 position;
		/*Linear velocity of the particle in world space*/
		Vector3 velocity;
		/*Acceleration of the particle: can be used to set
		the acceleration due to gravity (its primary use)
		or any other constant acceleration*/
		Vector3 acceleration;

		/*Amount of damping applied to linear motion. The first law of motion
		states that an object continues with a constant velocity (momentum really) unless a force
		acts upon it. Moving objects in real world will slow and come to
		a stop of they aren't being constantly forced along. That's why we need 
		the force of drag (approximation). Without it, the object will continue 
		to move at the same speed forever
		This controls how velocity is left after each update. O means velocity is
		reduced to nothing*/
		float damping;

		/*The inverse mass of the particle. The second law of motion gives us the
		mechanism by which forces alter the motion of an object. A force is
		something that changes the acceleration of an object (rate of change of velocity).
		=>We CANNOT do anything to an object to directly change its position or velocity;
		we CAN only do that by applying a force to change ACCELERATION and wait until
		the object reaches the target position or velocity.
		So if we directly set the velocity or position, the particle will appear to
		jolt or jump. They should only be altered by the integrator not set manually.
		Acceleration however can be set at any time.
		========>acceleration = 1/m * force or momentum
		It is more useful to hold the inverse mass because integration is simpler
		and because in real time simulation it is more useful to have objects with
		infinite mass(immovable) than zero mass*/
		float inverseMass;

		Vector3 forceAccum;


		/*Gravitational law between an object (small) and the earth(big)
		force = mg
		acceleration = 1/m * force = 1/m * mg = g
		=> NO MATTER WHAT MASS THE OBJECT HAS, IT WILL ALWAYS ACCELERATE AT THE
		SAME RATE DUE TO GRAVITY
		=> THE MOST SIGNIFICANT FORCE WE NEED TO APPLY CAN BE APPLIED DIRECTLY AS
		AN ACCELERATION. FOR NOW, GRAVITY IS THE SOLE FORCE AT WORK ON PARTICLES, AND
		WILL APPLY DIRECTLY AS AN ACCELERATION*/


		/*Integrate the particle forward in time by the given amount*/
		void integrate(float duration) {
			if (duration > 0) {
				//	Update linear position: p' = p + pVelocity* deltaTime
				position.addScaledVector(velocity, duration);

				//	Work out the acceleration from force
				Vector3 resultingAcc = acceleration;
				resultingAcc.addScaledVector(forceAccum, inverseMass);

				//	Update linear velocity from acceleration: 
				//	pVelocity' = pVelocity + acceleration * deltaTime 
				velocity.addScaledVector(resultingAcc, duration);

				//	Impose drag
				velocity *= powf(damping, duration);
			}
		}

	};