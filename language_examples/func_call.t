let
  type my_record = {value : int}
  function reference(parameter : my_record) =
    parameter.value := 42
  /*function value(parameter : string) =
    parameter := "Tiger is the best language\n"*/
  var rec1 := my_record{value = 1}
in
  reference(rec1);
  print_int(rec1.value);
  print("\n");
  value(str);
  print(str);
  print("\n")
end
