import React from "react";
import { Todo } from "./Model";
import axios from "axios";


interface Props {
    todos: Todo[];
    todoIdToEdit: number | null;
    deleteTodo: (id:number) => void;
    toggleEdit: (id:number) => void;
    updateTodo: (id:number, todoAction:string) => void;
}


const TodoList:React.FC<Props> = ({ todos, deleteTodo, todoIdToEdit }) => {
    const [editing, setEditing] = React.useState(null)

    const toggleEdit = (id:number | null) => {
        todoIdToEdit = id;
        console.log(todoIdToEdit)
    }

    
    

    return (
        <div>
            {todos.map((todo) => (
                <div key={todo.id}>
                    <p>{todo.todoAction} | {todo.isComplete ? "True" : "False"}</p>
                    <button onClick={() => toggleEdit(todo.id)}>Update</button>
                    <button onClick={() => deleteTodo(todo.id)}>Delete</button>
                </div>
            ))}
        </div>
    )
}

export default TodoList;