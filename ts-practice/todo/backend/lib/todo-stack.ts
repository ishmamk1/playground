import * as cdk from 'aws-cdk-lib';
import { Construct } from 'constructs';
import * as lambda from "aws-cdk-lib/aws-lambda";
import * as apigateway from "aws-cdk-lib/aws-apigateway";
import * as path from "path";
import * as dynamodb from 'aws-cdk-lib/aws-dynamodb';
import { DynamoDBClient, PutItemCommand } from "@aws-sdk/client-dynamodb";


export class TodoStack extends cdk.Stack {
  public readonly table: dynamodb.Table;

  constructor(scope: Construct, id: string, props?: cdk.StackProps) {
    super(scope, id, props);

    // api gateway endpoint
    const api = new apigateway.RestApi(this, "HelloAPI", {
      restApiName: "Todo service",
    });

    this.table = new dynamodb.Table(this, 'Todo', {
      tableName: 'Todo',
      partitionKey: { name: 'id', type: dynamodb.AttributeType.STRING },
      billingMode: dynamodb.BillingMode.PAY_PER_REQUEST,
    });

    // GetTodos function and resource
    const getTodosFunction = new lambda.Function(this, "GetTodosFunction", {
      runtime: lambda.Runtime.NODEJS_22_X,
      handler: "getTodos.handler",
      code: lambda.Code.fromAsset(path.join(__dirname, "../lambda/dist")),
      timeout: cdk.Duration.seconds(10)
    });

    const getTodosResource = api.root.addResource("get_todos");
    getTodosResource.addCorsPreflight({
      allowOrigins: apigateway.Cors.ALL_ORIGINS,
      allowMethods: ["GET", "OPTIONS"]
    })

    getTodosResource.addMethod(
      "GET",
      new apigateway.LambdaIntegration(getTodosFunction)
    )

    // Delete todos function and resource

    const deleteTodoFunction = new lambda.Function(this, "DeleteTodoFunction", {
      runtime: lambda.Runtime.NODEJS_22_X,
      handler: "deleteTodo.handler",
      code: lambda.Code.fromAsset(path.join(__dirname, "../lambda/dist")),
      timeout: cdk.Duration.seconds(10)
    });

    const deleteTodoResource = api.root.addResource("delete_todo");
    deleteTodoResource.addCorsPreflight({
      allowOrigins: apigateway.Cors.ALL_ORIGINS,
      allowMethods: ["POST", "OPTIONS"]
    })

    deleteTodoResource.addMethod(
      "POST",
      new apigateway.LambdaIntegration(deleteTodoFunction)
    )

    // update item function and resource
    const updateTodoFunction = new lambda.Function(this, "UpdateTodoFunction", {
      runtime: lambda.Runtime.NODEJS_22_X,
      handler: "updateTodo.handler",
      code: lambda.Code.fromAsset(path.join(__dirname, "../lambda/dist")),
      timeout: cdk.Duration.seconds(10)
    });

    const updateTodoResource = api.root.addResource("update_todo");
    updateTodoResource.addCorsPreflight({
      allowOrigins: apigateway.Cors.ALL_ORIGINS,
      allowMethods: ["POST", "OPTIONS"]
    })

    updateTodoResource.addMethod(
      "POST",
      new apigateway.LambdaIntegration(updateTodoFunction)
    )

    // Add item function and resource
    const addTodoFunction = new lambda.Function(this, "AddTodoFunction", {
      runtime: lambda.Runtime.NODEJS_22_X,
      handler: "addTodo.handler",
      code: lambda.Code.fromAsset(path.join(__dirname, "../lambda/dist")),
      timeout: cdk.Duration.seconds(10)
    });

    const addTodoResource = api.root.addResource("add_todo");
    addTodoResource.addCorsPreflight({
      allowOrigins: apigateway.Cors.ALL_ORIGINS,
      allowMethods: ["POST", "OPTIONS"]
    })
    addTodoResource.addMethod(
      "POST",
      new apigateway.LambdaIntegration(addTodoFunction)
    )

    // Hello lambda function
    const helloFunction = new lambda.Function(this, "HelloFunction", {
      runtime: lambda.Runtime.NODEJS_22_X,
      handler: 'hello.handler',
      code: lambda.Code.fromAsset(path.join(__dirname, "../lambda/dist")),
    });


    // hello method
    const helloResource = api.root.addResource("hello");
    helloResource.addMethod("GET", new apigateway.LambdaIntegration(helloFunction, {
      integrationResponses: [{
        statusCode: '200',
        responseParameters: {
          'method.response.header.Access-Control-Allow-Origin': "'*'"
        },
        responseTemplates: { 'application/json': '' }
      }]
    }), {
      methodResponses: [{
        statusCode: '200',
        responseParameters: {
          'method.response.header.Access-Control-Allow-Origin': true
        }
      }]
    });
  }
}
