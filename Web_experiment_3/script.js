(() => {
  const display = document.querySelector('#calculator-display');
  const keys = document.querySelector('#calculator-keys');

  const state = {
    expression: '0',
    currentNumber: '0',
    operator: null,
    shouldResetDisplay: false,
  };

  function updateDisplay() {
    display.value = state.expression;
  }

  function resetCalculator() {
    state.expression = '0';
    state.currentNumber = '0';
    state.operator = null;
    state.shouldResetDisplay = false;
  }

  function inputDigit(digit) {
    if (state.expression === '错误') {
      resetCalculator();
    }

    if (state.shouldResetDisplay) {
      state.expression = digit;
      state.currentNumber = digit;
      state.shouldResetDisplay = false;
    } else {
      if (state.expression === '0') {
        state.expression = digit;
        state.currentNumber = digit;
      } else {
        state.expression += digit;
        state.currentNumber += digit;
      }
    }
  }

  function inputDecimal() {
    if (state.expression === '错误') {
      resetCalculator();
      return;
    }

    if (state.shouldResetDisplay) {
      state.expression = '0.';
      state.currentNumber = '0.';
      state.shouldResetDisplay = false;
      return;
    }

    if (!state.currentNumber.includes('.')) {
      state.expression += '.';
      state.currentNumber += '.';
    }
  }

  function formatResult(result) {
    const rounded = Math.round(result * 1e10) / 1e10;
    return rounded.toString();
  }

  function evaluateExpression(expr) {
    try {
      // 简单的表达式求值（安全处理）
      const sanitized = expr.replace(/[^0-9+\-*/.]/g, '');
      const result = Function('"use strict"; return (' + sanitized + ')')();
      return result;
    } catch {
      return NaN;
    }
  }

  function handleOperator(operatorSymbol) {
    if (state.expression === '错误') {
      return;
    }

    // 如果最后一个字符已经是运算符，替换它
    const lastChar = state.expression[state.expression.length - 1];
    if (['+', '-', '*', '/'].includes(lastChar)) {
      state.expression = state.expression.slice(0, -1) + operatorSymbol;
      state.operator = operatorSymbol;
    } else {
      state.expression += operatorSymbol;
      state.currentNumber = '';
      state.operator = operatorSymbol;
    }
  }

  function handleEquals() {
    if (state.expression === '错误' || state.expression === '0') {
      return;
    }

    // 检查表达式末尾是否为运算符
    const lastChar = state.expression[state.expression.length - 1];
    if (['+', '-', '*', '/'].includes(lastChar)) {
      return;
    }

    const result = evaluateExpression(state.expression);

    if (!Number.isFinite(result)) {
      state.expression = '错误';
      state.currentNumber = '0';
      state.operator = null;
      state.shouldResetDisplay = false;
      return;
    }

    state.expression = formatResult(result);
    state.currentNumber = state.expression;
    state.operator = null;
    state.shouldResetDisplay = true;
  }

  function handleBackspace() {
    if (state.expression === '错误') {
      resetCalculator();
      return;
    }

    if (state.shouldResetDisplay) {
      return;
    }

    if (state.expression.length <= 1) {
      state.expression = '0';
      state.currentNumber = '0';
    } else {
      const removedChar = state.expression[state.expression.length - 1];
      state.expression = state.expression.slice(0, -1);
      
      // 更新当前数字
      if (['+', '-', '*', '/'].includes(removedChar)) {
        state.operator = null;
      } else {
        state.currentNumber = state.currentNumber.slice(0, -1);
      }
    }
  }

  keys.addEventListener('click', (event) => {
    const button = event.target.closest('button');
    if (!button) {
      return;
    }

    const { action, value } = button.dataset;

    switch (action) {
      case 'digit':
        inputDigit(value);
        break;
      case 'decimal':
        inputDecimal();
        break;
      case 'add':
      case 'subtract':
      case 'multiply':
      case 'divide':
        handleOperator({ add: '+', subtract: '-', multiply: '*', divide: '/' }[action]);
        break;
      case 'equals':
        handleEquals();
        break;
      case 'clear':
        resetCalculator();
        break;
      case 'delete':
        handleBackspace();
        break;
      default:
        break;
    }

    updateDisplay();
  });

  updateDisplay();
})();

