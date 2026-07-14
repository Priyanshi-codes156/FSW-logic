let menuBtn = document.getElementById("menuBtn");
let dropdownMenu = document.getElementById("dropdownMenu");

menuBtn.addEventListener("click", function () {
  dropdownMenu.classList.toggle("hidden");
});

let menuLinks = dropdownMenu.querySelectorAll("a");
menuLinks.forEach(function (link) {
  link.addEventListener("click", function () {
    dropdownMenu.classList.add("hidden");
  });
});