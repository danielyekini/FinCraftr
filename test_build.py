#!/usr/bin/env python3
"""
Simple test script to verify FinCraftr installation and basic functionality.
"""

def test_cpp_extension():
    """Test the C++ extension if available."""
    try:
        import fincraftr as fc
        
        print("✓ Successfully imported fincraftr")
        
        # Test basic function
        result = fc.return_simple(105.0, 100.0)
        expected = 0.05
        assert abs(result - expected) < 1e-10, f"Expected {expected}, got {result}"
        print(f"✓ return_simple(105, 100) = {result}")
        
        # Test module access
        result2 = fc.equity.return_simple(110.0, 100.0)
        expected2 = 0.10
        assert abs(result2 - expected2) < 1e-10, f"Expected {expected2}, got {result2}"
        print(f"✓ equity.return_simple(110, 100) = {result2}")
        
        # Test other modules
        compound_result = fc.rates.compound_discrete(1000.0, 0.05, 12, 1.0)
        print(f"✓ rates.compound_discrete(1000, 0.05, 12, 1) = {compound_result}")
        
        call_payoff = fc.options.payoff_call(105.0, 100.0)
        expected_payoff = 5.0
        assert abs(call_payoff - expected_payoff) < 1e-10, f"Expected {expected_payoff}, got {call_payoff}"
        print(f"✓ options.payoff_call(105, 100) = {call_payoff}")
        
        forward_price = fc.forwards.forward_price_no_div(100.0, 0.05, 1.0)
        print(f"✓ forwards.forward_price_no_div(100, 0.05, 1) = {forward_price}")
        
        print("\n🎉 All C++ extension tests passed!")
        return True
        
    except ImportError as e:
        print(f"❌ Could not import C++ extension: {e}")
        return False
    except Exception as e:
        print(f"❌ Error testing C++ extension: {e}")
        return False

def test_python_fallback():
    """Test Python fallback implementations."""
    try:
        # Test if we can import the Python modules directly
        from python.fincraftr.equity import returns
        from python.fincraftr.rates import compounding
        from python.fincraftr.options import payoff
        from python.fincraftr.forwards import pricing
        
        print("✓ Successfully imported Python fallback modules")
        
        # These would be the Python implementations
        # For now, just verify the imports work
        print("✓ Python fallback modules available")
        return True
        
    except ImportError as e:
        print(f"❌ Could not import Python fallback: {e}")
        return False

def test_docstrings():
    """Test that docstrings are properly exposed."""
    try:
        import fincraftr as fc
        
        # Test that help works
        help_text = fc.return_simple.__doc__
        if help_text and "stock gain/lose" in help_text:
            print("✓ Docstrings properly exposed")
            return True
        else:
            print(f"⚠ Docstring may be missing or incomplete: {help_text}")
            return False
            
    except Exception as e:
        print(f"❌ Error testing docstrings: {e}")
        return False

def main():
    """Run all tests."""
    print("Testing FinCraftr installation...\n")
    
    tests = [
        ("C++ Extension", test_cpp_extension),
        ("Python Fallback", test_python_fallback), 
        ("Docstrings", test_docstrings),
    ]
    
    results = []
    for name, test_func in tests:
        print(f"\n--- Testing {name} ---")
        try:
            result = test_func()
            results.append((name, result))
        except Exception as e:
            print(f"❌ {name} test failed with exception: {e}")
            results.append((name, False))
    
    print("\n" + "="*50)
    print("SUMMARY:")
    for name, result in results:
        status = "✓ PASS" if result else "❌ FAIL"
        print(f"  {name}: {status}")
    
    total_passed = sum(1 for _, result in results if result)
    print(f"\nTotal: {total_passed}/{len(results)} tests passed")
    
    if total_passed == len(results):
        print("\n🎉 All tests passed! FinCraftr is working correctly.")
        return 0
    else:
        print(f"\n⚠ {len(results) - total_passed} tests failed.")
        return 1

if __name__ == "__main__":
    exit(main())
