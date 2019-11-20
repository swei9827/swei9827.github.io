using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Hazard : MonoBehaviour {

    Rigidbody2D rb;
    public float xSpeed;
    public float ySpeed;

    void Awake () {
        rb = GetComponent<Rigidbody2D>();
        xSpeed = Random.Range(0, 2);
        ySpeed = Random.Range(0, 2);
        Invoke("Despawn", 10.0f);
    }
	
	// Update is called once per frame
	void Update () {
        rb.velocity = new Vector2(xSpeed, ySpeed * -1);
    }

    void Despawn()
    {
        Destroy(this.gameObject);
    }

}
