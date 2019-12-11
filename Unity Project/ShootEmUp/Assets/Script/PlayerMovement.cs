using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerMovement : MonoBehaviour {

    Vector3 direction = Vector3.zero;
    public float speed = 2f;

    void Start () {
        Application.targetFrameRate = 60;
    }

	void Update () {
        Movement();
	}

    public void Movement()
    {
        direction.x = Input.GetAxis("Horizontal");
        direction.y = Input.GetAxis("Vertical");
        transform.Translate(direction * Time.deltaTime * speed, Space.World);
    }
}
    
