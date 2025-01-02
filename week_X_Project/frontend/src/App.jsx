import { useState, useEffect, useCallback } from "react";
import { javascript } from "@codemirror/lang-javascript";
import { python } from "@codemirror/lang-python";
import { cpp } from "@codemirror/lang-cpp";
import { html } from "@codemirror/lang-html";
import { css } from "@codemirror/lang-css";
import { sql } from "@codemirror/lang-sql";
import { java } from "@codemirror/lang-java";
import { Copy, Check, Menu, Trash2, Download, Search } from "lucide-react";
import axios from "axios";
import CodeEditor from "./components/CodeEditor";
import { useToast } from "./components/ui/use-toast";
import ThemeToggle from "./components/ThemeToggle";
import {
  ToastProvider,
  ToastViewport,
  Toast,
  ToastTitle,
  ToastDescription,
} from "./components/ui/Toast";


function App() {
  const [snippets, setSnippets] = useState([]);
  const [currentSnippet, setCurrentSnippet] = useState({
    title: "",
    code: "",
    language: "javascript",
    description: "",
  });

  const [copiedId, setCopiedId] = useState(null);
  const [searchTerm, setSearchTerm] = useState("");
  const [searchVisible, setSearchVisible] = useState(false);
  const [selectedLanguages, setSelectedLanguages] = useState([]);

  const { toast, toasts } = useToast();

  const [formErrors, setFormErrors] = useState({
    title: false,
    language: false,
    description: false,
    code: false,
  });

  const languageOptions = [
    { value: "javascript", label: "JavaScript", extension: javascript },
    { value: "java", label: "Java", extension: java },
    { value: "python", label: "Python", extension: python },
    { value: "cpp", label: "C++", extension: cpp },
    { value: "c", label: "C", extension: cpp },
    { value: "html", label: "HTML", extension: html },
    { value: "css", label: "CSS", extension: css },
    { value: "sql", label: "SQL", extension: sql },
  ];

  const getLanguageExtension = (languageValue) => {
    const language = languageOptions.find(
      (lang) => lang.value === languageValue
    );
    return language ? language.extension() : javascript();
  };

  // Keyboard shortcut handler
  const handleKeyboard = useCallback((e) => {
    if ((e.ctrlKey || e.metaKey) && e.key === "f") {
      e.preventDefault();
      setSearchVisible(true);
      document.getElementById("search-input")?.focus();
    }
    if (e.key === "Escape") {
      setSearchVisible(false);
    }
  }, []);

  useEffect(() => {
    window.addEventListener("keydown", handleKeyboard);
    return () => window.removeEventListener("keydown", handleKeyboard);
  }, [handleKeyboard]);

  useEffect(() => {
    const fetchSnippets = async () => {
      try {
        const response = await axios.get("http://localhost:5000/api/snippets");
        setSnippets(response.data);
      } catch (error) {
        console.error("Error fetching snippets:", error);
      }
    };
    fetchSnippets();
  }, []);

  const handleSubmit = async (e) => {
    e.preventDefault();

    const errors = {
      title: !currentSnippet.title.trim(),
      language: !currentSnippet.language.trim(),
      description: !currentSnippet.description.trim(),
      code: !currentSnippet.code.trim(),
    };

    setFormErrors(errors);

    if (errors.title || errors.language || errors.description || errors.code) {
      toast({
        variant: "destructive",
        title: "Empty fields",
        description: "Do not forget to fill in Title, Description and Code.",
      });
      return;
    }

    // Checking for duplicate title
    if (checkDuplicateTitle(currentSnippet.title)) {
      toast({
        variant: "destructive",
        title: "Duplicate Title",
        description:
          "A snippet with this title already exists. Please choose a different title.",
      });
      setFormErrors((prev) => ({ ...prev, title: true }));
      return;
    }

    try {
      const response = await axios.post(
        "http://localhost:5000/api/snippets",
        currentSnippet
      );
      setSnippets([response.data, ...snippets]);
      setCurrentSnippet({
        title: "",
        code: "",
        language: "javascript",
        description: "",
      });

      toast({
        title: "Success",
        description: "Snippet saved successfully!",
      });
    } catch (error) {
      console.error("Error saving snippet:", error);
      toast({
        variant: "destructive",
        title: "Error",
        description:
          error.response?.data?.message ||
          "Failed to save snippet. Please try again.",
      });
    }
  };

  const handleDelete = async (id) => {
    try {
      await axios.delete(`http://localhost:5000/api/snippets/${id}`);
      setSnippets(snippets.filter((snippet) => snippet._id !== id));
      toast({
        variant: "info",
        title: "Success!",
        description: "Snippet deleted successfully!",
      });
    } catch (error) {
      console.error("Error deleting snippet:", error);
      toast({
        variant: "destructive",
        title: "Error",
        description: "Failed to delete snippet. Please try again.",
      });
    }
  };

  const handleCopy = async (code, id) => {
    try {
      await navigator.clipboard.writeText(code);
      setCopiedId(id);
      setTimeout(() => setCopiedId(null), 2000);
      toast({
        title: "Success",
        description: "Code copied to clipboard!",
      });
    } catch (error) {
      console.error("Error copying to clipboard:", error);
      toast({
        variant: "destructive",
        title: "Error",
        description: "Failed to copy code. Please try again.",
      });
    }
  };

  const filteredSnippets = snippets.filter((snippet) => {
    const searchLower = searchTerm.toLowerCase();
    const matchesSearch =
      snippet.title.toLowerCase().includes(searchLower) ||
      snippet.description.toLowerCase().includes(searchLower) ||
      snippet.code.toLowerCase().includes(searchLower);
    const matchesLanguage =
      selectedLanguages.length === 0 ||
      selectedLanguages.includes(snippet.language);
    return matchesSearch && matchesLanguage;
  });

  const highlightMatches = (text, searchTerm) => {
    if (!searchTerm.trim()) return text;
    const regex = new RegExp(`(${searchTerm})`, "gi");
    return text.split(regex).map((part, i) =>
      regex.test(part) ? (
        <span key={i} className="bg-yellow-500/20 text-yellow-200">
          {part}
        </span>
      ) : (
        part
      )
    );
  };

  const exportSnippet = (snippet) => {
    const snippetData = {
      title: snippet.title,
      language: snippet.language,
      description: snippet.description,
      code: snippet.code,
      exportDate: new Date().toISOString(),
    };

    const blob = new Blob([JSON.stringify(snippetData, null, 2)], {
      type: "application/json",
    });
    const url = URL.createObjectURL(blob);
    const element = document.createElement("a");
    element.href = url;
    element.download = `${snippet.title
      .toLowerCase()
      .replace(/\s+/g, "-")}.json`;
    document.body.appendChild(element);
    element.click();
    document.body.removeChild(element);
    URL.revokeObjectURL(url);
  };

  const exportAllSnippets = () => {
    const exportData = {
      snippets: snippets.map((snippet) => ({
        title: snippet.title,
        language: snippet.language,
        description: snippet.description,
        code: snippet.code,
      })),
      exportDate: new Date().toISOString(),
    };

    const blob = new Blob([JSON.stringify(exportData, null, 2)], {
      type: "application/json",
    });
    const url = URL.createObjectURL(blob);
    const a = document.createElement("a");
    a.href = url;
    a.download = "all-snippets.json";
    document.body.appendChild(a);
    a.click();
    document.body.removeChild(a);
    URL.revokeObjectURL(url);
  };

  const checkDuplicateTitle = (title) => {
    return snippets.some(
      (snippet) =>
        snippet.title.toLowerCase() === title.toLowerCase() &&
        snippet._id !== currentSnippet._id
    );
  };

  return (
    <>
      <ToastProvider>
        <div className="flex h-screen bg-slate-800 dark:bg-slate-950">
          {/* Left Sidebar */}
          <aside className="w-[400px] bg-slate-800 dark:bg-slate-950 p-6 flex flex-col border-r border-slate-700 overflow-hidden">
          <div className="flex justify-between items-center mb-6">
            <h1 className="text-2xl font-bold text-white dark:text-slate-100">Code Library</h1>
            <ThemeToggle />
          </div>
            {/* Input Fields */}
            <div className="space-y-4 mb-6">
              <div>
                <label className="block text-sm font-medium text-slate-200 mb-2">
                  Title
                </label>
                <input
                  type="text"
                  value={currentSnippet.title}
                  onChange={(e) => {
                    const newTitle = e.target.value;
                    setCurrentSnippet((prev) => ({ ...prev, title: newTitle }));
                    if (checkDuplicateTitle(newTitle)) {
                      setFormErrors((prev) => ({ ...prev, title: true }));
                    } else {
                      setFormErrors((prev) => ({ ...prev, title: false }));
                    }
                  }}
                  className={`w-full p-2 rounded bg-slate-700 dark:bg-slate-800 text-white border ${
                    formErrors.title ? 'border-red-500' : 'border-slate-600 dark:border-slate-700'
                  } focus:outline-none focus:border-blue-500`}
                  required
                />
                {formErrors.title &&
                checkDuplicateTitle(currentSnippet.title) ? (
                  <p className="text-red-500 text-xs">
                    This title is already in use.
                  </p>
                ) : formErrors.title ? (
                  <p className="text-red-500 text-xs">Title is required.</p>
                ) : null}
              </div>

              <div>
                <label className="block text-sm font-medium text-slate-200 mb-2">
                  Language
                </label>
                <select
                  value={currentSnippet.language}
                  onChange={(e) =>
                    setCurrentSnippet({
                      ...currentSnippet,
                      language: e.target.value,
                    })
                  }
                  className={`w-full p-2 rounded bg-slate-700 text-white border ${
                    formErrors.language ? "border-red-500" : "border-slate-600"
                  } focus:outline-none focus:border-blue-500`}
                >
                  {languageOptions.map((option) => (
                    <option key={option.value} value={option.value}>
                      {option.label}
                    </option>
                  ))}
                </select>
                {formErrors.language && (
                  <p className="text-red-500 text-xs">Language is required.</p>
                )}
              </div>

              <div>
                <label className="block text-sm font-medium text-slate-200 mb-2">
                  Description
                </label>
                <textarea
                  value={currentSnippet.description}
                  onChange={(e) =>
                    setCurrentSnippet({
                      ...currentSnippet,
                      description: e.target.value,
                    })
                  }
                  className={`w-full p-2 rounded bg-slate-700 text-white border ${
                    formErrors.description
                      ? "border-red-500"
                      : "border-slate-600"
                  } focus:outline-none focus:border-blue-500`}
                  rows="3"
                />
                {formErrors.description && (
                  <p className="text-red-500 text-xs">
                    Description is required.
                  </p>
                )}
              </div>

              {formErrors.code && (
                <p className="text-red-500 text-xs">Code is required.</p>
              )}
            </div>

            {/* Search Section */}
            <div className={`mb-4 space-y-2 ${!searchVisible && "hidden"}`}>
              <div className="relative">
                <input
                  id="search-input"
                  type="text"
                  placeholder="Search snippets... (Press Esc to close)"
                  value={searchTerm}
                  onChange={(e) => setSearchTerm(e.target.value)}
                  className="w-full p-2 pl-8 rounded bg-slate-700 text-white border border-slate-600 focus:outline-none focus:border-blue-500"
                />
                <Search className="absolute left-2.5 top-2.5 h-4 w-4 text-slate-400" />
                <div className="absolute right-2 top-2 text-xs text-slate-400">
                  Ctrl + F
                </div>
              </div>

              {/* Language filter tags */}
              <div className="flex flex-wrap gap-2">
                {languageOptions.map((lang) => (
                  <button
                    key={lang.value}
                    onClick={() =>
                      setSelectedLanguages((prev) =>
                        prev.includes(lang.value)
                          ? prev.filter((l) => l !== lang.value)
                          : [...prev, lang.value]
                      )
                    }
                    className={`px-2 py-1 rounded text-xs ${
                      selectedLanguages.includes(lang.value)
                        ? "bg-blue-500 text-white"
                        : "bg-slate-700 text-slate-300 hover:bg-slate-600"
                    }`}
                  >
                    {lang.label}
                  </button>
                ))}
              </div>
            </div>

            {/* Saved Snippets Header */}
            <div className="flex justify-between items-center mb-3">
              <h2 className="text-lg font-semibold text-white">
                Saved Snippets
              </h2>
              <div className="flex items-center gap-2">
                <button
                  onClick={() => setSearchVisible(true)}
                  className="flex items-center gap-1 px-2 py-1 text-sm text-slate-300 hover:text-white transition-colors"
                  title="Search snippets (Ctrl + F)"
                >
                  <Search className="w-4 h-4" />
                </button>
                {snippets.length > 0 && (
                  <button
                    onClick={exportAllSnippets}
                    className="flex items-center gap-1 px-2 py-1 text-sm text-slate-300 hover:text-white transition-colors"
                    title="Export all snippets"
                  >
                    <Download className="w-4 h-4" />
                    <span>Export All</span>
                  </button>
                )}
              </div>
            </div>

            {/* Snippets List */}
            <div className="flex-1 overflow-auto">
              {filteredSnippets.length === 0 ? (
                <p className="text-slate-400 text-sm">
                  {snippets.length === 0
                    ? "No snippets created yet. Create your first snippet!"
                    : "No snippets found matching your search."}
                </p>
              ) : (
                <div className="space-y-2">
                  {filteredSnippets.map((snippet) => (
                    <div
                      key={snippet._id}
                      className="bg-slate-700 dark:bg-slate-800 rounded p-3 flex items-center justify-between hover:bg-slate-600 
                      dark:hover:bg-slate-700 ctransition-colors cursor-pointer group"
                      onClick={() => setCurrentSnippet(snippet)}
                    >
                      <div className="flex items-center gap-3">
                        <Menu className="w-4 h-4 text-slate-400" />
                        <div>
                          <h3 className="text-white font-medium text-sm">
                            {highlightMatches(snippet.title, searchTerm)}
                          </h3>
                          <span className="text-xs text-slate-400">
                            {
                              languageOptions.find(
                                (lang) => lang.value === snippet.language
                              )?.label
                            }
                          </span>
                          {searchTerm &&
                            (snippet.description
                              .toLowerCase()
                              .includes(searchTerm.toLowerCase()) ||
                              snippet.code
                                .toLowerCase()
                                .includes(searchTerm.toLowerCase())) && (
                              <p className="text-xs text-slate-300 mt-1 truncate max-w-[250px]">
                                {highlightMatches(
                                  snippet.description.includes(searchTerm)
                                    ? snippet.description
                                    : snippet.code,
                                  searchTerm
                                )}
                              </p>
                            )}
                        </div>
                      </div>
                      <div className="flex gap-2">
                        <button
                          onClick={(e) => {
                            e.stopPropagation();
                            handleCopy(snippet.code, snippet._id);
                          }}
                          className="opacity-0 group-hover:opacity-100 transition-opacity"
                        >
                          {copiedId === snippet._id ? (
                            <Check className="w-4 h-4 text-green-400" />
                          ) : (
                            <Copy className="w-4 h-4 text-slate-400 hover:text-white" />
                          )}
                        </button>
                        <button
                          onClick={(e) => {
                            e.stopPropagation();
                            handleDelete(snippet._id);
                          }}
                          className="opacity-0 group-hover:opacity-100 transition-opacity"
                        >
                          <Trash2 className="w-4 h-4 text-red-400 hover:text-red-300" />
                        </button>
                        <button
                          onClick={(e) => {
                            e.stopPropagation();
                            exportSnippet(snippet);
                          }}
                          className="opacity-0 group-hover:opacity-100 transition-opacity"
                          title="Export snippet"
                        >
                          <Download className="w-4 h-4 text-slate-400 hover:text-white" />
                        </button>
                      </div>
                    </div>
                  ))}
                </div>
              )}
            </div>
          </aside>

          {/* Main Content */}
          <main className="flex-1 flex flex-col h-screen">
            <div className="flex-1 relative h-[calc(100vh-60px)]">
              <CodeEditor
                value={currentSnippet.code}
                onChange={(value) =>
                  setCurrentSnippet({ ...currentSnippet, code: value })
                }
                language={currentSnippet.language}
                extensions={[getLanguageExtension(currentSnippet.language)]}
              />
            </div>
            <footer className="h-[60px] flex items-center justify-end px-6 bg-slate-800 dark:bg-slate-950 border-t border-slate-700">
              <button
                onClick={handleSubmit}
                className="bg-blue-600 text-white px-6 py-2 rounded hover:bg-blue-700 transition-colors"
              >
                Save Snippet
              </button>
            </footer>
          </main>
        </div>
        {toasts &&
          toasts.map((toast) => (
            <Toast key={toast.id} variant={toast.variant}>
              <div className="grid gap-1">
                <ToastTitle>{toast.title}</ToastTitle>
                {toast.description && (
                  <ToastDescription>{toast.description}</ToastDescription>
                )}
              </div>
            </Toast>
          ))}
        <ToastViewport />
      </ToastProvider>
    </>
  );
}

export default App;
