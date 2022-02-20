{
    for ( i = 1 ; i <= NF ; i++ ) {
        gsub(/\s/, "", $i)
        if ( index($i,"'") > 0 ) {
            printf("%s", substr($i,index($i,"'")+1,1)) ;
        } else {
            switch ($i) {
                case "0x5D" : {printf(" "); break ; }
                case "0x59U" : {printf("*"); break ; }
                case "0x8AU" : {printf(":"); break ; }
                case "0x83U" : {printf("?"); break ; }
                case "0x84U" : {printf("."); break ; }
                case "0x85U" : {printf(","); break ; }
                case "0x82U" : {printf("!"); break ; }
                default : {printf(" %s ", $i); break ; }
            }
        }
    }
    printf("\n") ;
}
