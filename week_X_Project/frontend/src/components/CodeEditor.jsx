import { useEffect, useState } from "react";
import CodeMirror from "@uiw/react-codemirror";
import styles from "../styles/CodeMirror.module.css";
import { EditorView } from "@codemirror/view";
import PropTypes from "prop-types";

const CodeEditor = ({ value, onChange, extensions }) => {
    const [currentTheme, setCurrentTheme] = useState(localStorage.getItem('theme'));

    useEffect(() => {
        const handleThemeChange = () => {
            setCurrentTheme(localStorage.getItem('theme'));
        };

        window.addEventListener('themeChange', handleThemeChange);
        return () => window.removeEventListener('themeChange', handleThemeChange);
    }, []);

    return (
        <div className={styles.editorContainer}>
            <CodeMirror
                value={value}
                height="100%"
                width="100%"
                theme={currentTheme === 'dark' ? 'dark' : 'light'}
                extensions={[
                    ...extensions,
                    EditorView.theme({
                        '&': {
                            backgroundColor: currentTheme === 'dark' ? '#1e293b' : '#ffffff',
                            color: currentTheme === 'dark' ? '#ffffff' : '#1e293b',
                        },
                        '.cm-content': {
                            color: currentTheme === 'dark' ? '#ffffff' : '#1e293b',
                            caretColor: currentTheme === 'dark' ? '#ffffff' : '#1e293b'
                        },
                        '&.cm-focused .cm-cursor': {
                            borderLeftColor: currentTheme === 'dark' ? '#ffffff' : '#1e293b'
                        },
                        '&.cm-focused .cm-selectionBackground, ::selection': {
                            backgroundColor: currentTheme === 'dark' ? 'rgba(255,255,255,0.2)' : 'rgba(0,0,0,0.2)'
                        },
                        '.cm-gutters': {
                            backgroundColor: currentTheme === 'dark' ? '#1e293b' : '#ffffff',
                            color: currentTheme === 'dark' ? '#ffffff' : '#1e293b',
                            borderRight: currentTheme === 'dark' ? '1px solid #334155' : '1px solid #e2e8f0'
                        }
                    })
                ]}
            onChange={onChange}
            className={styles.editor}
            style={{ fontSize: '14px' }}
            basicSetup={{
            lineNumbers: true,
            highlightActiveLineGutter: true,
            highlightSpecialChars: true,
            foldGutter: true,
            drawSelection: true,
            dropCursor: true,
            allowMultipleSelections: true,
            indentOnInput: true,
            bracketMatching: true,
            closeBrackets: true,
            autocompletion: true,
            rectangularSelection: true,
            crosshairCursor: true,
            highlightActiveLine: true,
            highlightSelectionMatches: true,
            closeBracketsKeymap: true,
            defaultKeymap: true,
            searchKeymap: true,
            historyKeymap: true,
            foldKeymap: true,
            completionKeymap: true,
            lintKeymap: true,
            }}
        />
        </div>
    );
};

CodeEditor.propTypes = {
    value: PropTypes.string.isRequired,
    onChange: PropTypes.func.isRequired,
    extensions: PropTypes.array.isRequired,
};

export default CodeEditor;
