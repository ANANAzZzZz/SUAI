    using UnityEngine;

public class PlayerPickUpDrop : MonoBehaviour
{
    [SerializeField] private Transform playerCameraTransform;
    [SerializeField] private Transform objectGrabPointTransform;
    [SerializeField] private GameObject waterGameObject;

    private float pickUpDistance = 2f;
    private ObjectGrabbable objectGrabbable;

    private void LateUpdate()
    {
        if (Input.GetKeyDown(KeyCode.Mouse0))
        {
            if (!objectGrabbable)
            {
             // Not carrying an object, try to grab
                if (Physics.Raycast(
                        playerCameraTransform.position,
                        playerCameraTransform.forward,
                        out RaycastHit raycastHit,
                        pickUpDistance
                    ))
                {
                    if (raycastHit.transform.TryGetComponent(out objectGrabbable))
                    {
                        objectGrabbable.Grab(objectGrabPointTransform, playerCameraTransform);
                    }
                }
            }
            else
            {
             // Currently carrying smth, drop
             objectGrabbable.Drop();
             objectGrabbable = null;
            }
        }

        else if (Input.GetKeyDown(KeyCode.Mouse1))
        {
            if (objectGrabbable.name == "bucket")
            {

                {
                    if (!GameObject.Find("Particle System"))
                    {
                        Destroy(waterGameObject);
                    }
                }
            }
        }
    } 
}