
// Веневцев Артем Андреевич ЭФБО-06-24

function cub(number) {

    return number**3;

}

let arr = [];
let chislo = 5;

for (let i = 1; i <= chislo; i++) {

    arr[i] = Math.floor(Math.random() * 100) ; // рандомное значение от 0 до ста

}

for (let i = 1; i <= chislo; i++) {
    // console.log( arr[i] );
    console.log( cub(arr[i]) );
}