using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

[Serializable]
public struct Entry : IComparable<Entry> {

    public string entryName;
    public int score;

    public Entry(string n,int s)
    {
        this.entryName = n;
        this.score = s;
    }

    public int CompareTo(Entry other)
    {
        return other.score - this.score;
    }
}

[Serializable]
public struct EntryList
{
    public List<Entry> entries;

}