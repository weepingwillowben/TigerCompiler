let type any = {any : int}
    var buffer : string := getchar()
function readint(any: any) : int =
    let var i := 0
        function isdigit(s : string) : int =
            ord(buffer)>=ord("0") & ord(buffer)<=ord("9")
    in
        while
        buffer=" "
        |
         buffer="\n"
        do
        buffer := getchar();
            any.any := isdigit(buffer);
            while isdigit(buffer)
                do (i := i*10+ord(buffer)-ord("0");
                    buffer := getchar());
        i
end

type list = {first: int, rest: list}

function readlist() : list =
    let var any := any{any=0}
        var i := readint(any)
    in if any.any
        then list{first=i,rest=readlist()}
        else (buffer := getchar(); nil)
    end

function merge(a: list, b: list) : list =
    if a=nil then b
    else if b=nil then a
    else if a.first < b.first
        then list{first=a.first,rest=merge(a.rest,b)}
        else list{first=b.first,rest=merge(a,b.rest)}
function printint(i: int) =
    let function f(i:int) = if i>0
        then (f(i/10); print(chr(i-i/10*10+ord("0"))))
    in if i<0 then (print("-"); f(-i))
        else if i>0 then f(i)
        else print("0")
    end
function printlist(l: list) =
    if l=nil then print("\n")
    else (printint(l.first); print(" "); printlist(l.rest))
    /* BODY OF MAIN PROGRAM */
in
    printlist(merge(readlist(), readlist()))
end
