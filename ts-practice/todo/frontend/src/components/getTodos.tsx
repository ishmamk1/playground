import React, { useEffect, useState } from 'react';

interface Todo {
  id: string;
  item: string;
}

const GetTodos: React.FC = () => {
  const [todos, setTodos] = useState<Todo[]>([]);
  const [loading, setLoading] = useState<boolean>(true);
  const [error, setError] = useState<string | null>(null);
  const [message, setMessage] = useState<string>('');
  const [editingTodoId, setEditingTodoId] = useState<string | null>(null);
  const [editText, setEditText] = useState<string>('');

  const fetchTodos = async () => {
    try {
      const response = await fetch('http://127.0.0.1:3000/get_todos');
      if (!response.ok) throw new Error('Failed to fetch todos');
      const data = await response.json();
      setTodos(data.listItems || []);
    } catch (err: any) {
      setError(err.message);
    } finally {
      setLoading(false);
    }
  };

  const deleteTodo = async (id: string) => {
    try {
      const response = await fetch('http://127.0.0.1:3000/delete_todo', {
        method: 'POST',
        body: JSON.stringify({ id }),
      });

      const data = await response.json();

      if (response.ok) {
        setMessage(`✅ ${data.message}`);
        setTodos((prevTodos) => prevTodos.filter((todo) => todo.id !== id));
      } else {
        setMessage(`❌ Error: ${data.error || data.message}`);
      }
    } catch (err: any) {
      setMessage(`❌ Failed to delete todo: ${err.message}`);
    }
  };

  const updateTodo = async (id: string, item: string) => {
    try {
      const response = await fetch('http://127.0.0.1:3000/update_todo', {
        method: 'POST',
        body: JSON.stringify({ id, item }),
      });

      const data = await response.json();

      if (response.ok) {
        setMessage(`✅ ${data.message}`);
        setTodos((prevTodos) =>
          prevTodos.map((todo) => (todo.id === id ? { ...todo, item } : todo))
        );
        setEditingTodoId(null);
        setEditText('');
      } else {
        setMessage(`❌ Error: ${data.error || data.message}`);
      }
    } catch (err: any) {
      setMessage(`❌ Failed to update todo: ${err.message}`);
    }
  };

  useEffect(() => {
    fetchTodos();
  }, []);

  if (loading) return <p>Loading todos...</p>;
  if (error) return <p>Error: {error}</p>;

  return (
    <div style={{ padding: '1rem' }}>
      <h2>Todo List</h2>
      {message && <p>{message}</p>}
      <ul>
        {todos.map((todo) => (
          <li key={todo.id} style={{ marginBottom: '0.5rem' }}>
            {editingTodoId === todo.id ? (
              <>
                <input
                  type="text"
                  value={editText}
                  onChange={(e) => setEditText(e.target.value)}
                  style={{ marginRight: '0.5rem' }}
                />
                <button onClick={() => updateTodo(todo.id, editText)}>
                  Save
                </button>
                <button onClick={() => setEditingTodoId(null)} style={{ marginLeft: '0.5rem' }}>
                  Cancel
                </button>
              </>
            ) : (
              <>
                {todo.item}
                <button
                  onClick={() => {
                    setEditingTodoId(todo.id);
                    setEditText(todo.item);
                  }}
                  style={{ marginLeft: '1rem', color: 'blue' }}
                >
                  Edit
                </button>
                <button
                  onClick={() => deleteTodo(todo.id)}
                  style={{ marginLeft: '0.5rem', color: 'red' }}
                >
                  Delete
                </button>
              </>
            )}
          </li>
        ))}
      </ul>
    </div>
  );
};

export default GetTodos;



