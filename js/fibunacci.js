(function(){
  var fibonacci = function (n) {
      return n < 2 ? n : fibonacci(n - 1) + fibonacci(n - 2);
  };

  fibonacci(12);
  print( 'fibonacci->' , fibonacci(11) );
}());
