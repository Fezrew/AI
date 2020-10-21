#include "KeyboardBehaviour.h"

void KeyboardBehaviour::Update(Agent* agent, float deltaTime)
{
    Vector2 force = Vector2Zero();

    if (IsKeyDown(KEY_UP))
        force.y = -m_speedIncrement;
    if (IsKeyDown(KEY_DOWN))
        force.y = m_speedIncrement;
    if (IsKeyDown(KEY_LEFT))
        force.x = -m_speedIncrement;
    if (IsKeyDown(KEY_RIGHT))
        force.x = m_speedIncrement;

    agent->AddForce(force);

//    float X = agent->GetSpeed().x;
//    float Y = agent->GetSpeed().y; 
//    float Accel = agent->GetAcceleration(); 
//    float Decel = agent->GetDeceleration();
//
//#ifdef ROTATE
//
//#else
//    if (IsKeyDown(KEY_W))
//    {
//        agent->SetSpeed({ X, Y - Accel });
//        UpdateSpeed(agent, X, Y, Accel, Decel);
//    }
//    if (IsKeyDown(KEY_S))
//    {
//        agent->SetSpeed({ X, Y + Accel });
//        UpdateSpeed(agent, X, Y, Accel, Decel);
//    }
//    // if neither are pressed then reduce the acceleration
//    if (!(IsKeyDown(KEY_W)) && !(IsKeyDown(KEY_S)))
//    {
//        agent->SetSpeed({ X, Y - (Y / Accel * Decel) });
//        UpdateSpeed(agent, X, Y, Accel, Decel);
//    }
//    if (IsKeyDown(KEY_A))
//    {
//        agent->SetSpeed({ X - Accel, Y });
//        UpdateSpeed(agent, X, Y, Accel, Decel);
//    }
//    if (IsKeyDown(KEY_D))
//    {
//        agent->SetSpeed({ X + Accel, Y });
//        UpdateSpeed(agent, X, Y, Accel, Decel);
//    }
//    // if neither are pressed then reduce the acceleration
//    if (!(IsKeyDown(KEY_A)) && !(IsKeyDown(KEY_D)))
//    {
//        agent->SetSpeed({ X - (X / Accel * Decel), Y });
//        UpdateSpeed(agent, X, Y, Accel, Decel);
//    }
//#endif
//
//    agent->SetVelocity({ X * deltaTime, Y * deltaTime });
}
//
//void KeyboardBehaviour::UpdateSpeed(Agent* agent, float& X, float& Y, float& Accel, float& Decel)
//{
//    X = agent->GetSpeed().x;
//    Y = agent->GetSpeed().y;
//    Accel = agent->GetAcceleration();
//    Decel = agent->GetDeceleration();
//}
