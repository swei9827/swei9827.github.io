using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System.IO;
using System;
using UnityEngine.UI;

public class LeaderboardManager : MonoBehaviour {

    public string newEntryName;
    public int newEntryScore;
    public GameObject EntryTemplate;
    public Transform contentPanel;

    private List<GameObject> entryRenderers = new List<GameObject>();

    private void Start()
    {
        RenderLeaderboard();
    }

    public void RenderLeaderboard()
    {
        // Purge renderers
        foreach(GameObject go in entryRenderers)
        {
            Destroy(go);
        }

        entryRenderers = new List<GameObject>();
        
        EntryList data = this.LoadEntries();
        EntryTemplate.SetActive(false);

        data.entries.Sort();

        for(int i=0;i<data.entries.Count;i++)
        {
            GameObject newEntry = Instantiate(EntryTemplate, contentPanel);
            entryRenderers.Add(newEntry);

            newEntry.GetComponent<EntryRenderer>().Initialize(i + 1, data.entries[i].entryName, data.entries[i].score);
            newEntry.SetActive(true);

            if(i % 2 == 0)
            {
                newEntry.GetComponent<Image>().color = Color.gray;
            }
        }
    }

    [ContextMenu("Save and Update")]
    public void SaveAndupdate()
    {
        SaveEntry();
        RenderLeaderboard();
    }

    [ContextMenu("Save an Entry")]
    public void SaveEntry()
    {
        Debug.Log("Saving Entry");

        Entry entry = new Entry(this.newEntryName, newEntryScore);

        EntryList loadedData = this.LoadEntries();

        bool newEntry = true;

        for(int i= 0; i<loadedData.entries.Count;i++)
        {
            if(loadedData.entries[i].entryName == this.newEntryName)
            {
                newEntry = false;
                if(this.newEntryScore > loadedData.entries[i].score)
                {
                    loadedData.entries[i] = new Entry(this.newEntryName, this.newEntryScore);
                }
            }
        }

        if (newEntry == true) loadedData.entries.Add(entry);

        // Convert our Entry struct into a JSON string format
        string data = JsonUtility.ToJson(loadedData,true);

        Debug.Log(data);

        // Write and save our JSON string to a text file in a specific folder

        string path = Path.Combine(Application.streamingAssetsPath,"Score");

        File.WriteAllText(path, data);

        #if UNITY_EDITOR
        UnityEditor.AssetDatabase.Refresh();
        #endif

    }

    [ContextMenu("Load Entry")]
    public EntryList LoadEntries()
    {
        Debug.Log("Loading Entries");
        EntryList newList = new EntryList();
        newList.entries = new List<Entry>();

        // get path to score file
        string path = Path.Combine(Application.streamingAssetsPath, "Score");

        if(File.Exists(path))
        {
            string json = File.ReadAllText(path);
            newList = JsonUtility.FromJson<EntryList>(json);
        }
        return newList;
    }
}
