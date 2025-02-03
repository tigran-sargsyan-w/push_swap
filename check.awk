#!/usr/bin/awk -f
# Process the first line: count it and initialize the previous operation variable.
NR == 1 {
    op[$0]++          # Count this operation.
    total++           # Increase total operations count.
    prev = $0         # Set previous operation.
    next              # Proceed to the next line.
}

{
    # Count the current operation.
    op[$0]++
    total++

    # --- Merge operations ---
    # ra + rb -> rr (in any order)
    if ((prev == "ra" && $0 == "rb") || (prev == "rb" && $0 == "ra"))
        merge_ra_rb++
    # rra + rrb -> rrr (in any order)
    if ((prev == "rra" && $0 == "rrb") || (prev == "rrb" && $0 == "rra"))
        merge_rra_rrb++
    # sa + sb -> ss (in any order)
    if ((prev == "sa" && $0 == "sb") || (prev == "sb" && $0 == "sa"))
        merge_sa_sb++

    # --- Cancel operations ---
    # ra and rra cancel each other (in any order)
    if ((prev == "ra" && $0 == "rra") || (prev == "rra" && $0 == "ra"))
        cancel_ra_rra++
    # rb and rrb cancel each other (in any order)
    if ((prev == "rb" && $0 == "rrb") || (prev == "rrb" && $0 == "rb"))
        cancel_rb_rrb++
    # Double application of sa cancels out
    if (prev == "sa" && $0 == "sa")
        cancel_sa_sa++
    # Double application of sb cancels out
    if (prev == "sb" && $0 == "sb")
        cancel_sb_sb++
    # Double application of ss cancels out
    if (prev == "ss" && $0 == "ss")
        cancel_ss_ss++
    # pa and pb cancel each other if the element returns to its original position
    if ((prev == "pa" && $0 == "pb") || (prev == "pb" && $0 == "pa"))
        cancel_pa_pb++
    # rr and rrr cancel each other (in any order)
    if ((prev == "rr" && $0 == "rrr") || (prev == "rrr" && $0 == "rr"))
        cancel_rr_rrr++

    # Update the previous operation.
    prev = $0
}

END {
    # Print the total number of operations.
    print "Total number of operations:", total

    # Print the count for each individual operation (including those not used).
    print "\nIndividual operation counts:"
    # Define the list of all possible operations.
    all_ops[1]  = "sa"
    all_ops[2]  = "sb"
    all_ops[3]  = "ss"
    all_ops[4]  = "pa"
    all_ops[5]  = "pb"
    all_ops[6]  = "ra"
    all_ops[7]  = "rb"
    all_ops[8]  = "rr"
    all_ops[9]  = "rra"
    all_ops[10] = "rrb"
    all_ops[11] = "rrr"
    
    for (i = 1; i <= 11; i++) {
        opName = all_ops[i]
        print "  " opName " :", op[opName] + 0
    }

    # Print the counts for merge (complementary) operations.
    print "\nPossible merge operations:"
    print "  ra + rb  -> rr  :", merge_ra_rb + 0
    print "  rra + rrb -> rrr :", merge_rra_rrb + 0
    print "  sa + sb  -> ss  :", merge_sa_sb + 0

    # Print the counts for cancel operations.
    print "\nPossible cancel operations:"
    print "  ra + rra      :", cancel_ra_rra + 0
    print "  rb + rrb      :", cancel_rb_rrb + 0
    print "  sa + sa       :", cancel_sa_sa + 0
    print "  sb + sb       :", cancel_sb_sb + 0
    print "  ss + ss       :", cancel_ss_ss + 0
    print "  pa + pb       :", cancel_pa_pb + 0
    print "  rr + rrr      :", cancel_rr_rrr + 0
}
