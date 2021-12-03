Array.from(document.getElementById("table").children[0].children)
  .splice(1)
  .map((tr) => ({
    case: tr.children[0].innerText,
    rank: Number(tr.children[1].innerHTML),
  }))
  .sort((f, s) => s.rank - f.rank)
  .splice(0, 400)
  .map((s) => {
    if (s.case.startsWith("small")) {
      return "small/" + s.case;
    }
    if (s.case.startsWith("medium")) {
      return "medium/" + s.case;
    }
    if (s.case.startsWith("large")) {
      return "large/" + s.case;
    }
  })
  .join(";");
