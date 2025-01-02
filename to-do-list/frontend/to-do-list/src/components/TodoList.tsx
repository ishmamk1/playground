import React from "react";
import { Todo } from "./Model";
import axios from "axios";


interface Props {
    todos: Todo[];
    todoIdToEdit: number | null;
    deleteTodo: (id:number) => void;
    updateTodo: (id:number, todoAction:string) => void;
    toggleEdit: (id:number | null) => void;
}


const TodoList:React.FC<Props> = ({ todos, deleteTodo, updateTodo, todoIdToEdit, toggleEdit }) => {
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
                  <p>{todo.todoAction} | {todo.isComplete ? "True" : "False"}</p>
                  <button onClick={() => {
                    toggleEdit(todo.id);
                    setEditText(todo.todoAction); // Initialize the input with the current text
                  }}>
                    Update
                  </button>
                  <button onClick={() => deleteTodo(todo.id)}>Delete</button>
                </div>
              )}
            </div>
          ))}
        </div>
      );
}

export default TodoList;