import React from "react";
import { Todo } from "./Model";
import axios from "axios";


interface Props {
    todos: Todo[];
    todoIdToEdit: number | null;
    deleteTodo: (id:number) => void;
    updateTodo: (id:number, todoAction:string) => void;
    toggleEdit: (id:number | null) => void;
    checkTodo: (id:number) => void;
}


const TodoList:React.FC<Props> = ({ todos, deleteTodo, updateTodo, todoIdToEdit, toggleEdit, checkTodo }) => {
    const [editText, setEditText] = React.useState("");

    const handleEditChange = (e:React.ChangeEvent<HTMLInputElement>) => {
        setEditText(e.target.value);
    };
    
    return (
        <div>
          {todos.map((todo) => (
            <div key={todo.id}>
              {todoIdToEdit === todo.id ? (
                // Show input for the todo being edited
                <div>
                  <input
                    type="text"
                    value={editText}
                    onChange={handleEditChange}
                    autoFocus
                  />
                  <button onClick={() => {updateTodo(todo.id, editText); toggleEdit(null);}}>Save</button>
                  <button onClick={() => toggleEdit(null)}>Cancel</button>
                </div>
              ) : (
                // Show static text for todos not in edit mode
                <div>
                    {todo.isCompleted ? (
                    <p style={{ textDecoration: "line-through", color: "gray" }}>
                        {todo.todoAction}
                        {todo.isCompleted}
                    </p>
                    ) : (
                    <div>
                        <p>{todo.todoAction}</p>
                        <p>{todo.isCompleted}</p>
                    </div>
                    )}
                    <button
                    onClick={() => {
                        toggleEdit(todo.id);
                        setEditText(todo.todoAction); // Initialize the input with the current text
                    }}
                    >
                    Update
                    </button>
                  <button onClick={() => deleteTodo(todo.id)}>Delete</button>
                  <button onClick={() => checkTodo(todo.id)}>Check</button>
                </div>
              )}
            </div>
          ))}
        </div>
      );
}

export default TodoList;