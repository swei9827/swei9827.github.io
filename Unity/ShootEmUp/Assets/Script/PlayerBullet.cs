using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class PlayerBullet : MonoBehaviour {

    public float bulletSpeed;

    void Start()
    {
        Invoke("Despawn", 2f);
    }

    void Update()
    {
        Move();
    }

    void Move()
    {
        this.transform.Translate(Vector3.up * Time.deltaTime * bulletSpeed);
    }

    void Despawn()
    {
        Destroy(this.gameObject);
    }

    private void OnTriggerEnter2D(Collider2D col)
    {
        if(col.gameObject.tag == "Enemy")
        {
            col.gameObject.GetComponent<Enemy>().health--;
            Despawn();
        }
    }
}
