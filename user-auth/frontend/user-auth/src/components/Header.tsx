import React from "react";
import "./css-styling/component.css"

interface Props {
    pageTitle: string;
    logoSrc: string;
}


const Header:React.FC<Props> = ( {pageTitle, logoSrc } ) => {

    return (
        <header className="App-header">
            <img src={logoSrc} className="App-logo"></img>
            <h1 className="App-title">{pageTitle}</h1>
        </header>
    );
}

export default Header;
