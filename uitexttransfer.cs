using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using TMPro;


public class UItextTransfer : MonoBehaviour
{
    public TextMeshProUGUI output;
    public TMP_InputField userName;
    public List<string> inputHistory = new List<string>();

    private void UpdateOutput()
    {
        string formattedOutput = string.Join("\n", inputHistory);
        output.text = $"Ingredient History:\n{formattedOutput}";
    }

    public void textTransfer()
    {
        string userInput = userName.text;
        if(!string.IsNullOrEmpty(userInput)){
            inputHistory.Add(userInput);
            UpdateOutput();
        }

    }
    public List<string> getInputHistory(){
        return new List<string>(inputHistory);
    }

}

