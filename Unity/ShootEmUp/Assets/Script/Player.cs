using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Player : MonoBehaviour
{

    public int health;

    void Start()
    {
        health = 5;
    }

    void Update()
    {

    }

    void OnCollisionEnter2D(Collision2D col)
    {
        if (col.gameObject.tag == "Enemy")
        {
            Damage();
            if (health <= 0)
            {

            }
        }
    }

    void Damage()
    {
        health--;
    }

    void Despawn()
    {
        Destroy(this.gameObject);
    }

}