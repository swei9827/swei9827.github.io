using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class EntryRenderer : MonoBehaviour {

    public Text rankLabel;
    public Text nameLabel;
    public Text scoreLabel;

    public void Initialize(int _rank,string _name, int _score)
    {
        rankLabel.text = _rank.ToString();
        nameLabel.text = _name.ToString();
        scoreLabel.text = _score.ToString();
    }
}
