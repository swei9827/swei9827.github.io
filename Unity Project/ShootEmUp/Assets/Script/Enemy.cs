using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Enemy : MonoBehaviour {

    Rigidbody2D rb;

    public float xSpeed;
    public float ySpeed;
    public int score;
    public GameObject enemyBullet;
    public Transform[] spawnPoint;
    public float fireRate;
    public int health;

    private void Awake()
    {
        rb = GetComponent<Rigidbody2D>();

    }
    void Start () {
        InvokeRepeating("Shoot", 0.5f, fireRate);
        Invoke("Despawn", 10.0f);
	}
	
	void Update () {
        rb.velocity = new Vector2(xSpeed, ySpeed * -1);
        if(health <= 0)
        {
            PlayerPrefs.SetInt("Score", PlayerPrefs.GetInt("Score") + score);
            Despawn();
        }
	}

    private void OnCollisionEnter2D(Collision2D col)
    {
        if(col.gameObject.tag == "Player")
        {
            col.gameObject.GetComponent<Player>().health--;

            Despawn();
        }
    }

    void Shoot()
    {
        for (int i = 0; i < spawnPoint.Length; i++)
        {
            Instantiate(enemyBullet, spawnPoint[i].position, this.transform.rotation);
        }
    }

    void Despawn()
    {
        Destroy(this.gameObject);
    }

}
