using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Policy;
using System.Text;
using System.Threading.Tasks;

using Hazel;

namespace Sandbox
{
    public class Camera : Entity
    {
        public float DistanceFromPlayer = 0.0f;

        void OnCreate()
        {
            Translation = new Vector3(Translation.XY, DistanceFromPlayer);
        }

        void OnUpdate(float ts)
        {
            Entity Player = FindEntityByName("Player");
            if (Player != null)
            {
                Translation = new Vector3(Player.Translation.XY, DistanceFromPlayer);
            }

            float speed = 1.0f;
            Vector3 velocity = Vector3.Zero;

            if(Input.IsKeyDown(KeyCode.HZ_KEY_UP))
            {
                velocity.Y = 1.0f;
            }
            else if(Input.IsKeyDown(KeyCode.HZ_KEY_DOWN))
            {
                velocity.Y = -1.0f;
            }

            if (Input.IsKeyDown(KeyCode.HZ_KEY_LEFT))
            {
                velocity.X = -1.0f;
            }
            else if (Input.IsKeyDown(KeyCode.HZ_KEY_RIGHT))
            {
                velocity.X = 1.0f;
            }

            velocity *= speed;

            //DistanceFromPlayer += ts;

            Vector3 translation = Translation;
            translation += velocity * ts;
            Translation = translation;
        }

    }
}
