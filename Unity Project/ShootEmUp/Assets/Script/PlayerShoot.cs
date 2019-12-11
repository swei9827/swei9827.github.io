using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlayerShoot : MonoBehaviour {

    public int shootCooldown;
    public int shootDelay;
    public GameObject bullet;
    public Transform[] spawnPoint;

    void Start () {
        Application.targetFrameRate = 60;
    }
	
	void Update () {
        shootCooldown++;
        if (shootCooldown>=shootDelay)
        {
            Shoot();
        }
        
	}

    public void Shoot()
    {
        if (Input.GetButton("Fire1"))
        {
            for (int i = 0; i < spawnPoint.Length; i++)
            {
                Instantiate(bullet, spawnPoint[i].position, this.transform.rotation);
            }
            shootCooldown = 0;
        }
    }
}
