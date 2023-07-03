using UnityEngine;

public class Interactive : MonoBehaviour
{
    [SerializeField] private Camera personCamera;

    private Ray ray;
    private RaycastHit hit;
    private float maxDistanceRay = 3f;

    public AudioSource source;
    public AudioClip successSound;
    public AudioClip failSound;
    public GameObject ParticleSystem;

    void Update()
    {
        Ray();
        TargetObject();
    }

    private void Ray()
    {
        ray = personCamera.ScreenPointToRay(new Vector2(Screen.width / 2, Screen.height / 2));
    }

    private void TargetObject()
    {
        if (Input.GetKeyDown(KeyCode.E))
        {
            if (Physics.Raycast(ray, out hit, maxDistanceRay))
            {
                if (hit.collider.gameObject.name == "TransformatorBox")
                {
                    if (GameObject.Find("Particle System"))
                    {
                        source.PlayOneShot(failSound);
                    }
                    else
                    {
                        source.PlayOneShot(successSound);
                    }
                }

                if (hit.collider.gameObject.name == "ButtonElectricity")
                {
                    Destroy(ParticleSystem);
                }
            }
        }
    }
}