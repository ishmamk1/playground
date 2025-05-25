import { DynamoDBClient } from "@aws-sdk/client-dynamodb";
import { ScanCommand, ScanCommandOutput } from "@aws-sdk/lib-dynamodb";
import { APIGatewayProxyEvent, APIGatewayProxyResult } from "aws-lambda";
import { unmarshall } from "@aws-sdk/util-dynamodb";

const client = new DynamoDBClient({
    region: "us-east-1",
    endpoint: "http://host.docker.internal:8000",
    credentials: {
        accessKeyId: "fakeMyKeyId",
        secretAccessKey: "fakeSecretAccessKey"
      }
});

export const handler = async ( 
    event: APIGatewayProxyEvent): Promise<APIGatewayProxyResult> => {
    
    try {
        const command = new ScanCommand({
            TableName: "Todo",
        });

        const response: ScanCommandOutput = await client.send(command);

        if (!response.Items) {
            return {
            statusCode: 404,
            body: JSON.stringify({ message: "No items found in Todo table" }),
            };
        }

        return {
            statusCode: 200,
            body: JSON.stringify({
                listItems: response.Items,
            }),
            headers: {
            'Content-Type': 'application/json'
            }
        };
    } catch (error) {
        return {
            statusCode: 500,
            body: JSON.stringify({
                message: "Internal Server Error",
                error: error instanceof Error ? error.message : String(error),
              }),
        };
    }    
};

