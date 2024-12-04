using System.Runtime.InteropServices;
using UnityEngine;
using TMPro;

public class TestCSVfile : MonoBehaviour {
    public string fileName = "Assests/C++ files/Sorted-Recipes.csv";
    public TextMeshProUGUI outputTest;

    [DllImport("SortNew")]
    public static extern int readCSV(string file);

    [DllImport("SortNew")]
    public static extern int dummy(string s);
    public void TestReadCSV() {
        int CSV = readCSV(fileName);
        Debug.Log(CSV);
        
    }
    public void TestDummy(){
        int result = dummy(fileName);
        Debug.Log(result);
    }
}
