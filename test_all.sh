#!/bin/sh
# Comprehensive test script for all DAA practical assignments
# Run this script in WSL to test all programs

echo "=========================================="
echo "   DAA Practical Submission - Test Suite"
echo "=========================================="
echo ""

SUCCESS_COUNT=0
FAIL_COUNT=0

# Function to test a program
test_program() {
    local dir=$1
    local name=$2
    local exec=$3
    
    echo "Testing: $name"
    echo "Directory: $dir"
    
    if [ -d "$dir" ]; then
        cd "$dir"
        
        # Check if executable exists
        if [ -f "$exec" ]; then
            # Run the program
            if ./"$exec" > /dev/null 2>&1; then
                echo "Status: ✓ SUCCESS"
                SUCCESS_COUNT=$((SUCCESS_COUNT + 1))
                
                # Check if output.txt was created
                if [ -f "output.txt" ]; then
                    echo "Output file: ✓ Created"
                else
                    echo "Output file: ✗ Not found"
                fi
            else
                echo "Status: ✗ FAILED (execution error)"
                FAIL_COUNT=$((FAIL_COUNT + 1))
            fi
        else
            echo "Status: ✗ FAILED (executable not found)"
            FAIL_COUNT=$((FAIL_COUNT + 1))
        fi
        
        cd - > /dev/null
    else
        echo "Status: ✗ FAILED (directory not found)"
        FAIL_COUNT=$((FAIL_COUNT + 1))
    fi
    
    echo ""
}

# Test all assignments
test_program "1_Customer_Order_Sorting_System" "Customer Order Sorting (Merge Sort)" "merge_sort"
test_program "2_Movie_Recommendation_System" "Movie Recommendation (Quick Sort)" "quick_sort"
test_program "3_Emergency_Relief_Supply" "Emergency Relief Supply (Fractional Knapsack)" "fractional_knapsack"
test_program "4_Smart_Traffic_Management" "Smart Traffic Management (Dijkstra)" "dijkstra"
test_program "5_Multi_Stage_Delivery" "Multi-Stage Delivery (Multistage Graph)" "multistage_graph"
test_program "6_Disaster_Relief_Resource" "Disaster Relief Resource (0/1 Knapsack)" "knapsack_01"
test_program "7_University_Timetable_Scheduling_" "University Timetable (Graph Coloring)" "graph_coloring"
test_program "8_N_Queens_Problem" "N-Queens Problem (Backtracking)" "n_queens"

echo "=========================================="
echo "              Test Summary"
echo "=========================================="
echo "Total Tests: $((SUCCESS_COUNT + FAIL_COUNT))"
echo "Passed: $SUCCESS_COUNT"
echo "Failed: $FAIL_COUNT"
echo ""

if [ $FAIL_COUNT -eq 0 ]; then
    echo "All tests passed! ✓"
    exit 0
else
    echo "Some tests failed. Please check the errors above."
    exit 1
fi
