Array.from(document.getElementById("table").children[0].children)
  .splice(1)
  .filter((tr) => tr.children[1].innerHTML != "1")
  .map((tr) => tr.children[0].innerText);

