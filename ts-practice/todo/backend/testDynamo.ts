import {
    DynamoDBClient,
    ScanCommand,
    ScanCommandOutput,
  } from "@aws-sdk/client-dynamodb";
  
  // Create DynamoDB client pointed to local instance
  const client = new DynamoDBClient({
    region: "us-west-2",
    endpoint: "http://localhost:8000", // Pointing to local DynamoDB
  });
  
  async function getAllTodos() {
    try {
      const command = new ScanCommand({
        TableName: "TodoItems",
      });
  
      const response: ScanCommandOutput = await client.send(command);
  
      console.log("Items:", response.Items);
      return response.Items;
    } catch (err) {
      console.error("Failed to scan table:", err);
      throw err;
    }
  }
  
  getAllTodos();
  
