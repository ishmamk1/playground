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
    stats: {
        base_stat: number;
        effort: number;
        stat: {
            name: string;
            url: string;
        }
    }[]
}


(async function() {
    try {
        const listResponse = await fetch("https://pokeapi.co/api/v2/pokemon/");
        const list: PokemonList = await listResponse.json() as PokemonList;

        const dataResponse = await fetch(list.results[0].url);
        const data: Pokemon = await dataResponse.json() as Pokemon;
        console.log(data.stats);
    } catch (e) {
        console.error(e);
    }

})();