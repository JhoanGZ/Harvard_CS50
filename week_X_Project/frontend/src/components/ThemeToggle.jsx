import { Moon, Sun } from 'lucide-react';
import { useEffect, useState } from 'react';

const ThemeToggle = () => {
    const [darkMode, setDarkMode] = useState(() => {
        // Getting initial state from localStorage or system preference
        if (typeof window !== 'undefined') {
        const savedTheme = localStorage.getItem('theme');
        return savedTheme ? savedTheme === 'dark' : window.matchMedia('(prefers-color-scheme: dark)').matches;
        }
        return false;
    });

    useEffect(() => {
        if (darkMode) {
            document.documentElement.classList.add('dark');
            localStorage.setItem('theme', 'dark');
            window.dispatchEvent(new Event('themeChange'));
        } else {
            document.documentElement.classList.remove('dark');
            localStorage.setItem('theme', 'light');
            window.dispatchEvent(new Event('themeChange'));
        }
    }, [darkMode]);

    return (
        <button
        onClick={() => setDarkMode(!darkMode)}
        className="p-2 rounded-md bg-slate-700 hover:bg-slate-600 transition-colors"
        title={darkMode ? 'Switch to light mode' : 'Switch to dark mode'}
        >
        {darkMode ? (
            <Sun className="h-5 w-5 text-yellow-300" />
        ) : (
            <Moon className="h-5 w-5 text-slate-300" />
        )}
        </button>
    );
};

export default ThemeToggle;