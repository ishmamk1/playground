import fetch from "node-fetch";

interface PokemonList {
    count: number;
    next: string;
    previous?: string;
    results: {
        name: string,
        url: string;
    }[];
}

interface Pokemon {
    id: number;
    name: string;
    stats: {
        base_stat: number;
        effort: number;
        stat: {
            name: string;
            url: string;
        }
    }[]
}

const getPokemonList = async (): Promise<PokemonList> => {
    const listResponse = await fetch("https://pokeapi.co/api/v2/pokemon/");
    return await listResponse.json() as PokemonList;
}

const getPokemon = async (url: string): Promise<Pokemon> => {
    const pokemonResponse = await fetch(url);
    return await pokemonResponse.json() as Pokemon;
}

const getFirstPokemon = async (): Promise<Pokemon> => {
    return new Promise(async (resolve, reject) => {
        try {
            console.log("getting list");
            const list = await getPokemonList();
            const pokemon = await getPokemon(list.results[0].url);
            if (pokemon) {
                resolve(pokemon);
            } else {
                reject(new Error("Failed to fetch the first Pokemon"));
            }
        } catch (error) {
            reject(error);
        }
    });
}

(async function() {
    try {
        const list = await getPokemonList();
        
        const data = await Promise.all(list.results.map((pokemon) => getPokemon(pokemon.url)));
        console.log(data);
        console.log(">>> Done");

    } catch (e) {
        console.error(e);
    }

})();