import React from "react"

interface Props {
    todo:string;
    setTodo: React.Dispatch<React.SetStateAction<string>>;
    handleAdd: (e: React.FormEvent) => void;
}

const InputField:React.FC<Props> = ({todo, setTodo, handleAdd}) => {
    return (
        <div>
            <form className="input" onSubmit={handleAdd}>
                <input type="input" 
                    value={todo} 
                    onChange={(e) => setTodo(e.target.value)} 
                    placeholder="Enter a task" 
                    className="input_box">
                </input>
                <button className="input_submit" type="submit">Go</button>
            </form>
        </div>
    )
}

export default InputField;