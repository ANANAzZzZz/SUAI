using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ThrowBall : MonoBehaviour
{
    // initialize ball
    public GameObject ball;

    // balls spawn point
    public Transform spawnBalls;

    // strenght of throwing
    public float throwForce;

    // delay between throws
    private float rate = 0.9f;

    // time of throw
    private float nextThrow = 0.0f;

    void FixedUpdate()
    {
        // lmb is pressed and delay observed
        if (Input.GetButton("Fire1") && Time.time > nextThrow)
        {
            // time of throw = current time + delay
            nextThrow = Time.time + rate;
            // create copy of ball's prefab
            GameObject newBall = Instantiate(ball);
            // place copy of prefab on spawn point and add forward offset
            newBall.transform.position = spawnBalls.transform.position + spawnBalls.transform.forward;
            // add physics of rigid body, give inpulse to ball.
            newBall.GetComponent<Rigidbody>().AddForce(spawnBalls.forward * throwForce, ForceMode.Impulse);
        }
    }
}
