using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using System;

public class TileGenerator : MonoBehaviour {

    public Sprite[] tileSprites;
    [SerializeField] int rows;
    [SerializeField] int columns;
    int[,] tileMap;

    List<Transform> generatedTiles = new List<Transform>();
	
	void Update () {

#if UNITY_EDITOR
        if (Input.GetKeyDown(KeyCode.Alpha1)) RandomizeTileMap();
        if (Input.GetKeyDown(KeyCode.Alpha2)) HardCodeTileMap();
        if (Input.GetKeyDown(KeyCode.Alpha3)) GenerateTileMapFromFile();
#endif
    }

    void RandomizeTileMap()
    {
        this.tileMap = new int[rows, columns];

        for( int r = 0; r < rows; r++)
        {
            for(int c = 0; c < columns; c++)
            {
                this.tileMap[r, c] = UnityEngine.Random.Range(1, tileSprites.Length);
            }
        }

        RenderTileMap();
    }

    void HardCodeTileMap()
    {

        rows = 4;
        columns = 4;

        this.tileMap = new int[4,4]
        {
            {45,46,46,47},
            {45,46,46,47},
            {45,46,46,47},
            {45,46,46,47}
        };
        
        RenderTileMap();
    }

    void GenerateTileMapFromFile()
    {
        TextAsset textFile = Resources.Load("TileMap") as TextAsset;

        string data = textFile.text;

        // Get Col/Width
        string widthData = data.Substring(data.IndexOf("width=") + 6);
        widthData = widthData.Substring(0, widthData.IndexOf("\n"));
        this.columns = int.Parse(widthData);

        // Get Row/Height
        string heightData = data.Substring(data.IndexOf("height=") + 7);
        heightData = heightData.Substring(0, heightData.IndexOf("\n"));
        this.rows = int.Parse(heightData);

        string tileMapData = data.Substring(data.IndexOf("data=") + 5);
        string[] rowsData = tileMapData.Split(new[] {'\r','\n' }, StringSplitOptions.RemoveEmptyEntries);
        this.tileMap = new int[rows, columns];
        for (int r = 0; r < rowsData.Length; r++)
        {
            string[] columnsData = rowsData[r].Split(new[] { "," }, StringSplitOptions.RemoveEmptyEntries); 
            for (int c = 0; c < columnsData.Length; c++)
            {
                this.tileMap[r, c] = int.Parse(columnsData[c]);
            }
        }
        
        RenderTileMap();
    }

    void RenderTileMap()
    {
        GameObject tilePrefab = Resources.Load("Tile") as GameObject;

        // Delete all generated tiles
        foreach(Transform t in generatedTiles)
        {
            Destroy(t.gameObject);
        }

        // Reinit list of generatedTtiles
        generatedTiles = new List<Transform>();

        // Get Origin Point
        Vector2 origin = Vector2.zero;
        origin.x = (-columns / 2) + 0.5f;
        origin.y = (rows / 2) - 0.5f;

        for (int r = 0; r < tileMap.GetLength(0); r++)
        {
            for(int c = 0; c < tileMap.GetLength(1); c++)
            {
                // Instantiate a new tile object
                Transform tile = Instantiate(tilePrefab).transform;
                tile.SetParent(this.transform);

                // Add to generated list
                this.generatedTiles.Add(tile);

                // Render it
                int spriteID = tileMap[r, c];
                tile.GetComponent<Tile>().RenderSprite(tileSprites[spriteID]);

                // Offset it
                tile.position = new Vector2(origin.x + c, origin.y - r);
            }
        }
    }
}
