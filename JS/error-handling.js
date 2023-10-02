try {
  // block of code to try
  undefinedFunction();
} catch (err) {
  // block to handle errors
  console.log(err.message);
}

// Throw error

throw "My error message"; // throw a text

// Input validation

var x = document.getElementById("mynum").value; // get input value
try {
  if (x == "") throw "empty"; // error cases
  if (isNaN(x)) throw "not a number";
  x = Number(x);
  if (x > 10) throw "too high";
} catch (err) {
  // if there's an error
  document.write("Input is " + err); // output error
  console.error(err); // write the error in console
} finally {
  document.write("</br />Done"); // executed regardless of the try / catch result
}
