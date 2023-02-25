using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ObjectGrabbable : MonoBehaviour
{
    private Rigidbody objectRigidbody;
    private Transform ObjectGrabPointTransform;

    private void Awake()
    {
        objectRigidbody = GetComponent<Rigidbody>();
    }

    public void Grab(Transform objectGrabPointTransform, Transform playerCameraTransform)
    {
        objectRigidbody.transform.forward = playerCameraTransform.position;
        this.ObjectGrabPointTransform = objectGrabPointTransform;
        objectRigidbody.useGravity = false;
        objectRigidbody.isKinematic = true;
    }

    public void Drop()
    {
        this.ObjectGrabPointTransform = null;
        objectRigidbody.useGravity = true;
        objectRigidbody.isKinematic = false;
    }
    
    private void FixedUpdate()
    {
        if (ObjectGrabPointTransform)
        {
            float lerpSpeed = 10f;
            
            Vector3 newPosition = Vector3.Lerp(
                transform.position,
                ObjectGrabPointTransform.position,
                Time.deltaTime * lerpSpeed
                );
            
            objectRigidbody.MovePosition(newPosition);
        }
    }
}
