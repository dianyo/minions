"""
Type stubs for minions_cpp_py - C++ implementation of Minions protocol.

These stubs provide IDE support (autocompletion, type checking) for the
C++ Python bindings.
"""

from typing import List, Dict, Optional, Tuple, Callable, Any

__version__: str
__cpp__: bool

class Usage:
    """Token usage tracking for LLM API calls."""
    
    prompt_tokens: int
    completion_tokens: int
    
    def __init__(self) -> None: ...
    
    @property
    def total_tokens(self) -> int: ...
    
    def __iadd__(self, other: Usage) -> Usage: ...
    def __add__(self, other: Usage) -> Usage: ...
    
    def to_dict(self) -> Dict[str, int]: ...
    
    @staticmethod
    def from_dict(data: Dict[str, int]) -> Usage: ...


class Message:
    """Message structure for chat completions."""
    
    role: str
    content: str
    images: Optional[List[str]]
    
    def __init__(
        self,
        role: str,
        content: str,
        images: Optional[List[str]] = None
    ) -> None: ...
    
    def to_json(self) -> Dict[str, Any]: ...
    
    @staticmethod
    def from_json(data: Dict[str, Any]) -> Message: ...


class Client:
    """Abstract base class for LLM clients."""
    
    def chat(
        self,
        messages: List[Dict[str, str]],
        **kwargs: Any
    ) -> Tuple[List[str], Usage, List[str]]: ...
    
    @property
    def model_name(self) -> str: ...
    
    @property
    def supports_embeddings(self) -> bool: ...
    
    def embed(self, texts: List[str]) -> List[List[float]]: ...


class OllamaClient(Client):
    """Client for Ollama local inference server."""
    
    def __init__(
        self,
        model_name: str,
        host: str = "http://localhost:11434",
        temperature: float = 0.7,
        max_tokens: int = 2048,
        verbose: bool = False,
    ) -> None: ...


class OpenAIClient(Client):
    """Client for OpenAI API."""
    
    def __init__(
        self,
        model_name: str,
        api_key: Optional[str] = None,
        base_url: Optional[str] = None,
        temperature: float = 0.7,
        max_tokens: int = 2048,
    ) -> None: ...


class Minion:
    """
    Single-worker Minions protocol implementation.
    
    The Minion protocol enables a cloud supervisor model to coordinate
    with a local worker model that has access to the full context.
    """
    
    def __init__(
        self,
        local_client: Client,
        remote_client: Client,
        max_rounds: int = 3,
        callback: Optional[Callable[[str, Dict[str, Any], bool], None]] = None,
        log_dir: str = "minion_logs",
    ) -> None: ...
    
    def __call__(
        self,
        task: str,
        context: List[str],
        max_rounds: Optional[int] = None,
        doc_metadata: Optional[str] = None,
    ) -> Dict[str, Any]:
        """
        Execute the Minion protocol.
        
        Args:
            task: The task/question to answer
            context: List of context strings (documents)
            max_rounds: Override default max_rounds
            doc_metadata: Optional metadata about the documents
            
        Returns:
            Dict containing:
                - final_answer: str
                - supervisor_messages: List[Dict]
                - worker_messages: List[Dict]
                - remote_usage: Usage
                - local_usage: Usage
                - timing: Dict[str, float]
        """
        ...


class Minions:
    """
    Parallel-worker Minions protocol implementation.
    
    The Minions (plural) protocol processes documents in parallel,
    with the supervisor distributing tasks across multiple worker instances.
    """
    
    def __init__(
        self,
        local_client: Client,
        remote_client: Client,
        max_rounds: int = 5,
        max_jobs_per_round: int = 2048,
        callback: Optional[Callable[[str, Any, bool], None]] = None,
        log_dir: str = "minions_logs",
    ) -> None: ...
    
    def __call__(
        self,
        task: str,
        doc_metadata: str,
        context: List[str],
        max_rounds: Optional[int] = None,
        max_jobs_per_round: Optional[int] = None,
        num_tasks_per_round: int = 3,
        num_samples_per_task: int = 1,
    ) -> Dict[str, Any]:
        """
        Execute the Minions protocol.
        
        Args:
            task: The task/question to answer
            doc_metadata: Description of the document type
            context: List of context strings (documents)
            max_rounds: Override default max_rounds
            max_jobs_per_round: Maximum parallel jobs per round
            num_tasks_per_round: Number of distinct tasks per round
            num_samples_per_task: Samples per task
            
        Returns:
            Dict containing:
                - final_answer: str
                - meta: List[Dict]
                - timing: Dict[str, float]
                - local_usage: Dict
                - remote_usage: Dict
        """
        ...

