function getvalue(uri, id, src)
{
    var xhttp = new XMLHttpRequest();
    var params="";

    if ( src != undefined )
    {
        params = "?src=" + encodeURIComponent(document.getElementById(src).value);
    }

    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
       document.getElementById(id).innerHTML = this.responseText;
      }
    };

//    alert(uri+params);

    xhttp.open("GET", uri+params, true);
    xhttp.send();
}


function getkeyval()
{
    var xhttp = new XMLHttpRequest();

    var params = "?message=" + encodeURIComponent(document.getElementById('bbb').value) +
                "&key=" + encodeURIComponent(document.getElementById('aaa').value);

    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
       document.getElementById('ccc').innerHTML = this.responseText;
      }
    };

//    alert(uri+params);
    
    xhttp.open("GET", "encrypt"+params, true);
    xhttp.send();
}


function getkeyval2()
{
    var xhttp = new XMLHttpRequest();

    var params = "?message=" + decodeURIComponent(document.getElementById('ccc').value) +
                "&key=" + decodeURIComponent(document.getElementById('aaa').value);

    xhttp.onreadystatechange = function() {
      if (this.readyState == 4 && this.status == 200) {
       document.getElementById('bbb').innerHTML = this.responseText;
      }
    };

//    alert(uri+params);
    
    xhttp.open("GET", "decrypt"+params, true);
    xhttp.send();
}
