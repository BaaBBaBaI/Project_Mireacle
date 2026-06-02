import React, { useState, useEffect, useRef } from 'react';
import { 
  Search, 
  X, 
  ChevronRight, 
  Hammer, 
  BookOpen, 
  Palette, 
  Gem, 
  ArrowRight,
  HelpCircle
} from 'lucide-react';

const M3_THEME = {
  bgPrimary: '#FCFCF9',       
  bgCard: '#FFFFFF',          
  bgContainer: '#F3F4ED',     
  textPrimary: '#1A1C18',     
  textMuted: '#74796E',       
  primary: '#C99E25',         
  primaryHover: '#A88015',    
  primaryContainer: '#FFF8E1',
  success: '#386B52',         
  border: '#E0E4DB',          
  accentGlow: 'rgba(201, 158, 37, 0.08)'
};

const CATEGORIES = [
  { id: 'auctions', name: 'Аукционы', tags: ['аук', 'аукционы', 'торги', 'лоты'], icon: Hammer, desc: 'Публичные торги редких предметов' },
  { id: 'antiques', name: 'Антиквариат', tags: ['ант', 'антиквариат', 'старина', 'винтаж'], icon: Gem, desc: 'Исторические артефакты' },
  { id: 'books', name: 'Редкие Книги', tags: ['кни', 'книги', 'рукописи', 'фолианты'], icon: BookOpen, desc: 'Первые издания и манускрипты' },
  { id: 'digital', name: 'Цифровое Искусство', tags: ['циф', 'цифровое', 'арт', 'nft'], icon: Palette, desc: '3D-модели и крипто-арт' }
];

const DEMO_ITEMS = [
  { id: 1, title: 'Золотая чаша династии Мин', category: 'antiques', price: '450,000 $', currentBid: '482,000 $', isHot: true, timeLeft: '2ч 15м' },
  { id: 2, title: 'Редкие винные коллекции Бордо 1982', category: 'auctions', price: '12,000 $', currentBid: '15,500 $', isHot: false, timeLeft: '1д 4ч' },
  { id: 3, title: 'Оригинал "Одиссеи" Гомера (1488г)', category: 'books', price: '1,200,000 $', currentBid: '1,250,000 $', isHot: true, timeLeft: '4ч 12м' },
  { id: 4, title: 'Генеративный таймлапс "Metamorphosis"', category: 'digital', price: '4.5 ETH', currentBid: '5.2 ETH', isHot: false, timeLeft: '18ч 30м' }
];

const PERSONALIZED_GREETINGS = [
  { text: "Что будем искать сегодня?" },
  { text: "Какое сокровище вас интересует?" },
  { text: "Что интересного поищем сегодня?" },
  { text: "Какую категорию откроем сегодня?" },
  { text: "С чего начнем поиск шедевров?" }
];

export default function App() {
  const [greeting, setGreeting] = useState({ text: 'Что будем искать сегодня?' });
  const [searchQuery, setSearchQuery] = useState('');
  const [selectedCategory, setSelectedCategory] = useState(null);
  const [isFocused, setIsFocused] = useState(false);
  const [suggestions, setSuggestions] = useState({ categories: [], items: [] });
  
  const [isSearching, setIsSearching] = useState(false);
  const [searchResults, setSearchResults] = useState([]);
  const [searchExecuted, setSearchExecuted] = useState(false);

  const inputRef = useRef(null);

  useEffect(() => {
    const randomIdx = Math.floor(Math.random() * PERSONALIZED_GREETINGS.length);
    setGreeting(PERSONALIZED_GREETINGS[randomIdx]);
  }, []);

  useEffect(() => {
    if (!searchQuery.trim()) {
      setSuggestions({ categories: [], items: [] });
      return;
    }

    const queryLower = searchQuery.toLowerCase();

    // Поиск по категориям (если категория еще не выбрана)
    const matchedCategories = !selectedCategory ? CATEGORIES.filter(cat => {
      return cat.name.toLowerCase().includes(queryLower) || 
             cat.tags.some(tag => tag.startsWith(queryLower));
    }) : [];

    // Поиск по предметам
    let availableItems = DEMO_ITEMS;
    if (selectedCategory) {
      availableItems = availableItems.filter(item => item.category === selectedCategory.id);
    }

    const matchedItems = availableItems.filter(item =>
      item.title.toLowerCase().includes(queryLower)
    ).slice(0, 5);

    setSuggestions({ categories: matchedCategories, items: matchedItems });
  }, [searchQuery, selectedCategory]);

  const handleSelectCategory = (category) => {
    setSelectedCategory(category);
    setSearchQuery(''); 
    setSuggestions({ categories: [], items: [] });
    if (inputRef.current) {
      inputRef.current.focus();
    }
  };

  const handleRemoveCategory = () => {
    setSelectedCategory(null);
    setSearchQuery('');
    setSearchResults([]);
    setSearchExecuted(false);
    if (inputRef.current) {
      inputRef.current.focus();
    }
  };

  const handleSearchSubmit = (e, explicitQuery = null) => {
    if (e) e.preventDefault();
    
    setIsSearching(true);
    setSearchExecuted(true);

    const queryToSearch = explicitQuery !== null ? explicitQuery : searchQuery;
    if (explicitQuery !== null) setSearchQuery(explicitQuery);

    setTimeout(() => {
      let filtered = DEMO_ITEMS;
      
      if (selectedCategory) {
        filtered = filtered.filter(item => item.category === selectedCategory.id);
      }
      
      if (queryToSearch.trim()) {
        const text = queryToSearch.toLowerCase();
        filtered = filtered.filter(item => 
          item.title.toLowerCase().includes(text)
        );
      }

      setSearchResults(filtered);
      setIsSearching(false);
    }, 600);
  };

  const handleSelectItem = (item) => {
    setSearchQuery(item.title);
    handleSearchSubmit(null, item.title);
  };

  const handleClearAll = () => {
    setSearchQuery('');
    setSelectedCategory(null);
    setSearchResults([]);
    setSearchExecuted(false);
    setSuggestions({ categories: [], items: [] });
  };

  return (
    <div 
      className="min-h-screen flex flex-col justify-between font-sans transition-colors duration-300 relative overflow-x-hidden"
      style={{ 
        backgroundColor: M3_THEME.bgPrimary, 
        color: M3_THEME.textPrimary 
      }}
    >
      <div className="h-12 w-full shrink-0" />

      <main className="flex-1 flex flex-col items-center justify-center px-4 max-w-3xl w-full mx-auto pb-24">
        
        {/* Заголовок без иконки погоды */}
        <div className="text-center mb-8 flex flex-col items-center justify-center animate-in fade-in duration-500">
          <h2 className="text-2xl md:text-3xl font-medium tracking-tight leading-snug max-w-md">
            {greeting.text}
          </h2>
        </div>

        {/* ----------------- ПОИСКОВАЯ СТРОКА ----------------- */}
        <div className="w-full relative px-2">
          <form 
            onSubmit={(e) => handleSearchSubmit(e)}
            className={`w-full rounded-full border transition-all duration-400 ease-out flex flex-col ${
              isFocused 
                ? 'shadow-[0_12px_32px_rgba(201,158,37,0.12)] scale-[1.01]' 
                : 'shadow-[0_4px_20px_rgba(0,0,0,0.03)] hover:shadow-[0_6px_24px_rgba(0,0,0,0.05)]'
            }`}
            style={{ 
              backgroundColor: M3_THEME.bgCard, 
              borderColor: isFocused ? M3_THEME.primary : M3_THEME.border,
            }}
          >
            {/* Input Band */}
            <div className="flex items-center px-6 py-3.5 min-h-[64px] relative gap-3">
              <Search className="w-5 h-5 shrink-0 transition-colors duration-300" style={{ color: isFocused ? M3_THEME.primary : M3_THEME.textMuted }} />
              
              <div className="flex flex-wrap items-center gap-1.5 flex-1 min-w-0">
                {selectedCategory && (
                  <div 
                    className="inline-flex items-center space-x-1 py-1 px-3 rounded-full text-xs font-semibold animate-in zoom-in-95 duration-150 border"
                    style={{ 
                      backgroundColor: M3_THEME.primaryContainer, 
                      borderColor: `${M3_THEME.primary}33`,
                      color: M3_THEME.primary 
                    }}
                  >
                    <selectedCategory.icon className="w-3.5 h-3.5 shrink-0" />
                    <span>{selectedCategory.name}</span>
                    <button 
                      type="button" 
                      onClick={handleRemoveCategory}
                      className="hover:bg-black/5 p-0.5 rounded-full transition-colors ml-0.5"
                    >
                      <X className="w-3 h-3" />
                    </button>
                  </div>
                )}

                <input
                  ref={inputRef}
                  type="text"
                  value={searchQuery}
                  onChange={(e) => setSearchQuery(e.target.value)}
                  onFocus={() => setIsFocused(true)}
                  onBlur={() => setTimeout(() => setIsFocused(false), 200)}
                  placeholder={
                    selectedCategory 
                      ? `Искать в категории "${selectedCategory.name}"...` 
                      : "Введите категорию или название лота..."
                  }
                  className="bg-transparent border-none outline-none flex-1 min-w-[120px] text-sm md:text-base placeholder-opacity-60 transition-all duration-200"
                  style={{ color: M3_THEME.textPrimary }}
                />
              </div>

              {/* Action Buttons */}
              <div className="flex items-center space-x-1 shrink-0">
                {(searchQuery || selectedCategory) && (
                  <button
                    type="button"
                    onClick={handleClearAll}
                    className="p-1.5 rounded-full opacity-60 hover:opacity-100 hover:bg-black/5 transition-all"
                  >
                    <X className="w-4 h-4" />
                  </button>
                )}
                
                <button
                  type="submit"
                  disabled={isSearching}
                  className="w-10 h-10 rounded-full flex items-center justify-center transition-all duration-300 transform active:scale-95 shrink-0"
                  style={{ 
                    backgroundColor: M3_THEME.primary, 
                    color: '#FFFFFF',
                    boxShadow: `0 4px 10px ${M3_THEME.accentGlow}`
                  }}
                >
                  <ArrowRight className="w-4 h-4" />
                </button>
              </div>
            </div>
          </form>

          {/* ABSOLUTE EXPANDABLE DROP-DOWN (Появляется только во время набора текста) */}
          {isFocused && searchQuery.trim() && (suggestions.categories.length > 0 || suggestions.items.length > 0) && (
            <div 
              className="absolute left-2 right-2 top-full mt-3 rounded-3xl shadow-2xl z-50 overflow-hidden animate-in slide-in-from-top-2 fade-in duration-200 border"
              style={{ backgroundColor: M3_THEME.bgCard, borderColor: M3_THEME.border }}
            >
              <div className="py-2 max-h-[300px] overflow-y-auto">
                {/* 1. СОВПАДЕНИЯ ПО КАТЕГОРИЯМ */}
                {suggestions.categories.length > 0 && (
                  <div className="mb-2">
                    <p className="text-[10px] tracking-wider uppercase font-semibold opacity-50 px-4 py-2">
                      Категории
                    </p>
                    <div>
                      {suggestions.categories.map((cat) => {
                        const IconComponent = cat.icon;
                        return (
                          <button
                            key={cat.id}
                            type="button"
                            onMouseDown={(e) => { e.preventDefault(); handleSelectCategory(cat); }}
                            className="w-full text-left px-4 py-2.5 flex items-center justify-between transition-all duration-150 hover:bg-black/[0.03] group"
                          >
                            <div className="flex items-center space-x-3">
                              <div 
                                className="w-8 h-8 rounded-full flex items-center justify-center"
                                style={{ backgroundColor: M3_THEME.bgContainer }}
                              >
                                <IconComponent className="w-4 h-4" style={{ color: M3_THEME.primary }} />
                              </div>
                              <div>
                                <h4 className="text-sm font-semibold text-gray-800">{cat.name}</h4>
                                <p className="text-[11px] opacity-60">{cat.desc}</p>
                              </div>
                            </div>
                            <ChevronRight className="w-4 h-4 opacity-0 group-hover:opacity-100 transition-all transform translate-x-1 group-hover:translate-x-0" style={{ color: M3_THEME.primary }} />
                          </button>
                        );
                      })}
                    </div>
                  </div>
                )}

                {/* 2. СОВПАДЕНИЯ ПО ПРЕДМЕТАМ (Автозаполнение) */}
                {suggestions.items.length > 0 && (
                  <div>
                    {suggestions.categories.length > 0 && <div className="h-px w-full bg-black/5 my-1" />}
                    <p className="text-[10px] tracking-wider uppercase font-semibold opacity-50 px-4 py-2">
                      Предложения
                    </p>
                    <div>
                      {suggestions.items.map((item) => (
                        <button
                          key={item.id}
                          type="button"
                          onMouseDown={(e) => { e.preventDefault(); handleSelectItem(item); }}
                          className="w-full text-left px-4 py-2 flex items-center space-x-3 transition-all duration-150 hover:bg-black/[0.03] group"
                        >
                          <div className="w-8 h-8 flex items-center justify-center opacity-40 group-hover:opacity-100 transition-opacity">
                            <Search className="w-4 h-4" />
                          </div>
                          <div className="flex-1 min-w-0">
                            <h4 className="text-sm text-gray-800 truncate">{item.title}</h4>
                          </div>
                          <span className="text-xs opacity-0 group-hover:opacity-50 transition-opacity">
                            Выбрать
                          </span>
                        </button>
                      ))}
                    </div>
                  </div>
                )}
              </div>
            </div>
          )}
        </div>

        {/* ----------------- SEARCH RESULTS / DYNAMIC PREVIEW ----------------- */}
        <div className="w-full mt-10">
          {isSearching && (
            <div className="flex flex-col items-center justify-center py-10 space-y-3">
              <div 
                className="w-8 h-8 rounded-full border-2 border-t-transparent animate-spin"
                style={{ borderColor: M3_THEME.primary }}
              />
              <p className="text-xs tracking-wider opacity-60">Загрузка результатов поиска...</p>
            </div>
          )}

          {!isSearching && searchExecuted && (
            <div className="space-y-4 animate-in fade-in duration-200">
              <div className="flex items-center justify-between border-b pb-2" style={{ borderColor: M3_THEME.border }}>
                <h3 className="text-sm font-semibold tracking-wide uppercase opacity-75">
                  Результаты поиска ({searchResults.length})
                </h3>
                {selectedCategory && (
                  <span className="text-xs opacity-60">
                    категория: <span className="font-semibold text-black">{selectedCategory.name}</span>
                  </span>
                )}
              </div>

              {searchResults.length > 0 ? (
                <div className="grid grid-cols-1 md:grid-cols-2 gap-3">
                  {searchResults.map((item) => {
                    const matchedCat = CATEGORIES.find(c => c.id === item.category);
                    return (
                      <div 
                        key={item.id}
                        className="p-5 rounded-3xl border transition-all duration-200 flex flex-col justify-between group hover:shadow-md cursor-pointer"
                        style={{ 
                          backgroundColor: M3_THEME.bgCard, 
                          borderColor: M3_THEME.border 
                        }}
                      >
                        <div>
                          <div className="flex items-center justify-between mb-2">
                            <span 
                              className="text-[10px] px-2.5 py-0.5 rounded-full font-bold uppercase tracking-wider"
                              style={{ 
                                backgroundColor: M3_THEME.primaryContainer,
                                color: M3_THEME.primary
                              }}
                            >
                              {matchedCat?.name || item.category}
                            </span>
                            {item.isHot && (
                              <span className="text-[10px] text-rose-600 font-bold flex items-center space-x-1">
                                <span className="w-1.5 h-1.5 rounded-full bg-rose-500 animate-ping" />
                                <span>АКТИВНО</span>
                              </span>
                            )}
                          </div>
                          
                          <h4 className="font-semibold text-sm mb-1 text-gray-800">
                            {item.title}
                          </h4>
                        </div>

                        <div className="mt-4 pt-3 border-t flex items-center justify-between" style={{ borderColor: M3_THEME.border }}>
                          <div>
                            <p className="text-[9px] opacity-50 uppercase tracking-wider">Текущая ставка</p>
                            <p className="text-xs font-bold" style={{ color: M3_THEME.primary }}>{item.currentBid}</p>
                          </div>
                          <span className="text-[10px] opacity-65 font-medium">Осталось: {item.timeLeft}</span>
                        </div>
                      </div>
                    );
                  })}
                </div>
              ) : (
                <div 
                  className="p-10 text-center rounded-3xl border flex flex-col items-center space-y-2"
                  style={{ backgroundColor: M3_THEME.bgCard, borderColor: M3_THEME.border }}
                >
                  <HelpCircle className="w-6 h-6 opacity-40" />
                  <div>
                    <h4 className="font-semibold text-xs">Ничего не найдено</h4>
                    <p className="text-[11px] opacity-60 mt-0.5">
                      Попробуйте сбросить фильтр или ввести другое слово.
                    </p>
                  </div>
                  <button 
                    onClick={handleClearAll}
                    className="px-3 py-1.5 rounded-full border text-[11px] font-semibold hover:bg-black/[0.02] transition-all mt-1"
                    style={{ borderColor: M3_THEME.border }}
                  >
                    Сбросить настройки
                  </button>
                </div>
              )}
            </div>
          )}
        </div>

      </main>

      <div className="h-12 w-full shrink-0" />
    </div>
  );
}
