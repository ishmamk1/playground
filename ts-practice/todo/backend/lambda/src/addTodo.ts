import { DynamoDBClient, PutItemCommand } from "@aws-sdk/client-dynamodb";
import { ScanCommand, ScanCommandOutput } from "@aws-sdk/lib-dynamodb";
import { APIGatewayProxyEvent, APIGatewayProxyResult } from "aws-lambda";
import { unmarshall } from "@aws-sdk/util-dynamodb";
import { v4 as uuidv4 } from 'uuid';

const client = new DynamoDBClient({
    region: "us-east-1",
    endpoint: "http://host.docker.internal:8000",
    credentials: {
        accessKeyId: "fakeMyKeyId",
        secretAccessKey: "fakeSecretAccessKey"
      }
});

const corsHeaders = {
    "Access-Control-Allow-Origin": "*", // Or restrict to "http://localhost:5173"
    "Access-Control-Allow-Headers": "Content-Type",
    "Access-Control-Allow-Methods": "OPTIONS,POST",
  };

export const handler = async ( 
    event: APIGatewayProxyEvent): Promise<APIGatewayProxyResult> => {

    if (event.httpMethod === 'OPTIONS') {
        return {
            statusCode: 200,
            headers: {
            "Access-Control-Allow-Origin": "*",
            "Access-Control-Allow-Methods": "OPTIONS,POST"
            },
            body: ''
        };
    }
    try {
        if (!event.body) {
            return {
                statusCode: 400,
                body: JSON.stringify({ message: "missing request body"}),
            }
        }
          

        const requestData = JSON.parse(event.body);
        console.log(requestData);
        if (typeof requestData.item !== 'string' || requestData.item.trim() === '') {
            return {
              statusCode: 400,
              body: JSON.stringify({ message: "Invalid or missing 'item' field" }),
              headers: corsHeaders
            };
        }

        const id: string = uuidv4().toString();
        
        const command = new PutItemCommand({
            TableName: "Todo",
            Item: {
                id: { S: id },
                item: { S: requestData.item }
            }
        })

        const response = await client.send(command);

        return {
            statusCode: 200,
            body: JSON.stringify({
                message: "Item added!",
            }),
            headers: corsHeaders,
        };

    } catch (error) {
        return {
            statusCode: 500,
            body: JSON.stringify({
                message: "Internal Server Error",
                error: error instanceof Error ? error.message : String(error),
              }),
            headers: corsHeaders,
        };
    }
};