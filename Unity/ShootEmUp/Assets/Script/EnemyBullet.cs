using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyBullet : MonoBehaviour {

    public float bulletSpeed;

    void Start()
    {
        Invoke("Despawn", 5.0f);
    }

    void Update()
    {
        Move();
    }

    void Move()
    {
        this.transform.Translate(Vector3.down * Time.deltaTime * bulletSpeed);
    }

    void Despawn()
    {
        Destroy(this.gameObject);
    }

    private void OnTriggerEnter2D(Collider2D col)
    {
        if (col.gameObject.tag == "Player")
        {
            col.gameObject.GetComponent<Player>().health--;
            Despawn();
        }
    }
}
