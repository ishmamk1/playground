import React, { useEffect, useState } from 'react'
import axios from "axios";

import './App.css'
import InputField from './components/InputField';
import { Todo } from './components/Model';

import TodoList from './components/TodoList';

const App:React.FC = () =>  {

  const [todo, setTodo] = useState<string>("");
  const [todos, setTodos] = useState<Todo[]>([]);
  const [todoIdToEdit, setTodoIdToEdit] = useState<number | null>(null);
  
  const fetchTodos = async () => {
    try {
      const response = await axios.get('/api/v1/todo'); 
      console.log(response.data);
      setTodos(response.data);
      return response.data;
    } catch (err) {
      console.error("Error fetching todos:", err);
    }
  };

  const handleAdd = async (e:React.FormEvent) => {
    e.preventDefault();
    try {
      const response = await axios.post('/api/v1/todo', {
        todoAction: todo,
        isCompleted: false,
      });
      console.log("Response: " + response.data);
      setTodo(""); 
      fetchTodos();
    } catch (error){
      console.error("Todo not added: ", error)
    }
  }

  const deleteTodo = async (id: number) => {
    try {
      await axios.delete(`/api/v1/todo/${id}`); // Send DELETE request to the backend
      fetchTodos(); // Update the state
    } catch (error) {
      console.error("Error deleting todo:", error);
    }
  };

  const updateTodo = async (id: number, updateTodo:string) => {
    try {
      await axios.put(
        `/api/v1/todo/${id}`, // Ensure the endpoint matches your backend
        updateTodo, // Send the plain string as the request body
        {
          headers: {
            'Content-Type': 'text/plain', // Specify the content type as plain text
          },
        }
      );
      fetchTodos();
      console.log("Todo updated!");
    } catch (error) {
      console.error("Error", error);
    }
  }

  const toggleEdit = (id:number | null) => {
    setTodoIdToEdit(id);
    console.log(todoIdToEdit)
  }
  

  useEffect(() => {
    fetchTodos();
  }, []);

  return (
    <>
      <div>
        <span className="heading">To-Do List</span>
        <InputField todo={todo} setTodo ={setTodo} handleAdd={handleAdd}/>
        <button onClick={fetchTodos}>Fetch Todos</button> {/* Button to fetch on demand */}
        <TodoList todos={todos} deleteTodo={deleteTodo} updateTodo={updateTodo} todoIdToEdit={todoIdToEdit} toggleEdit={toggleEdit}></TodoList>
      </div>
    </>
  )
}

export default App
