using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class ShowPlayerScore : MonoBehaviour {

    public ManagerScript managerScript;

    void Awake () {
        PlayerPrefs.SetInt("Score", 0);
	}
	
	void Update () {
        GetComponent<Text>().text = PlayerPrefs.GetInt("Score") + "";
	}
}
