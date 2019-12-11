using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Spawner : MonoBehaviour {

    public float enemyRate;
    public float hazardRate;
    public GameObject[] enemies;
    public GameObject[] hazards;

	void Start () {
        InvokeRepeating("SpawnEnemy", enemyRate, enemyRate);
        InvokeRepeating("SpawnHazard", hazardRate, hazardRate);
    }
	
	public void SpawnEnemy()
    {
        Instantiate(enemies[(int)Random.Range(0, enemies.Length)], new Vector3(Random.Range(-9.0f, 9.0f), 7.0f), Quaternion.identity);
	}
    public void SpawnHazard()
    {
        Instantiate(hazards[(int)Random.Range(0, hazards.Length)], new Vector3(Random.Range(-9.0f, 9.0f), 7.0f), Quaternion.identity);
    }
}
